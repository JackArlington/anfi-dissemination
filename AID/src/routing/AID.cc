//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "AID.h"

using namespace Veins;

Define_Module(AID);

const simsignalwrap_t AID::mobilityStateChangedSignal = simsignalwrap_t(MIXIM_SIGNAL_MOBILITY_CHANGE_NAME);

void AID::initialize(int stage) {
    BaseWaveApplLayer::initialize(stage);

    if (stage == 0) {
        traci = TraCIMobilityAccess().get(getParentModule());

        dataRateTimer = new cMessage("datarate", SEND_DATA);
        datarate = par("datarate").doubleValue();

        duplicatedMessages = registerSignal("duplicatedMessages");
        messagesTransmitted = registerSignal("messagesTransmitted");
        messagesReceived = registerSignal("messagesReceived");
    }
}

void AID::finish() {
    BaseWaveApplLayer::finish();

    if (!messagesRcvd.empty()) {
        std::ofstream log;
        std::ostringstream o;

        o << "./results/" << par("log_traffic").longValue() << "-" << par("log_replication").longValue() << "-receiver-" << myId;
        log.open(o.str().c_str());

        for (std::map<int, MessageInfoEntry*>::iterator i = messagesRcvd.begin(); i != messagesRcvd.end(); i++) {
            MessageInfoEntry* videoInfo = i->second;

            log << videoInfo->receptionTime << " " << "id " << videoInfo->messageID << " " << "udp " << videoInfo->messageLength << endl;
        }
    }
}

void AID::handleSelfMsg(cMessage* msg) {
    switch (msg->getKind()) {

        case BROADCAST_TIMEOUT: {
            MessageInfoEntry* info = (MessageInfoEntry*) msg->getContextPointer();

            if (isMessageAlive(info) && isInsideROI(info)) {
                if (info->c > 1) {
                    int s = 0;
                    simtime_t interArrivalTimeBase = (info->broadcastTimer->getArrivalTime() - info->broadcastTimer->getCreationTime()) / info->c;

                    for (std::vector<simtime_t>::iterator i = info->deltaTimes.begin(); i != info->deltaTimes.end(); i++) {
                        if (interArrivalTimeBase - (*i) > 0) {
                            s--;
                        } else {
                            s++;
                        }
                    }
                    if (s > 0) {
                        addMessageToOutputQueue(info);
                    }
                } else {
                    addMessageToOutputQueue(info);
                }
            }

            delete info->broadcastTimer;
            info->broadcastTimer = NULL;

            break;
        }

        case SEND_DATA: {
            sendData();

            break;
        }

        default: {
            if (msg)
                EV << "AID - Error: Got Self Message of unknown kind! Name: " << msg->getName() << endl;
            break;
        }
    }
}

void AID::onBeacon(WaveShortMessage* wsm) {}

void AID::onData(WaveShortMessage* wsm) {
    DataMessage* dataMsg = dynamic_cast<DataMessage*>(wsm->decapsulate());

    MessageInfoEntry* info = new MessageInfoEntry;
    info->messageID = wsm->getSerial();
    info->messageOriginPosition = dataMsg->getMessageOriginPosition();
    info->messageROI = dataMsg->getMessageROI();
    info->messageOriginTime = dataMsg->getMessageOriginTime();
    info->messageTTL = dataMsg->getMessageTTL();
    info->hops = dataMsg->getHops() + 1;
    info->receptionTime = simTime();
    info->messageLength = wsm->getByteLength();
    info->c = 1;
    info->lastReceptionTime = simTime();
    info->broadcastTimer = NULL;

    if (!isMessageAlive(info) || !isInsideROI(info)) {
        delete info;
        delete dataMsg;

        return;
    }

    if (!isDuplicateMsg(info->messageID)) {
        double delay = uniform(0, par("randomDelayTimeMax").doubleValue());

        info->broadcastTimer = new cMessage("broadcast suppression", BROADCAST_TIMEOUT);
        info->broadcastTimer->setContextPointer((MessageInfoEntry*) info);
        scheduleAt(simTime() + delay, info->broadcastTimer);

        messagesRcvd[info->messageID] = info;
        emit(messagesReceived, 1);
    } else {
        delete info;
        MessageInfoEntry* info = messagesRcvd[wsm->getSerial()];

        if (info->broadcastTimer && info->broadcastTimer->isScheduled()) {
            info->c += 1;
            info->deltaTimes.push_back(simTime() - info->lastReceptionTime);
            info->lastReceptionTime = simTime();
        }

        emit(duplicatedMessages, 1);
    }

    delete dataMsg;
}

void AID::addMessageToOutputQueue(MessageInfoEntry* info) {
    if (std::find(outputQueue.begin(), outputQueue.end(), info->messageID) == outputQueue.end()) {
        outputQueue.push_back(info->messageID);
        if (!dataRateTimer->isScheduled()) {
            scheduleAt(simTime(), dataRateTimer);
        }
    }
}

void AID::sendData() {
    if (!outputQueue.empty()) {
        int nextMessageID = outputQueue.front();
        outputQueue.pop_front();
        MessageInfoEntry* info = messagesRcvd[nextMessageID];

        WaveShortMessage* wsm = createDataMsg(info);
        sendWSM(wsm);

        emit(messagesTransmitted, 1);

        double nextPktTime = info->messageLength / datarate;
        scheduleAt(simTime() + nextPktTime, dataRateTimer);
    }
}

bool AID::isDuplicateMsg(int messageID) {
    return messagesRcvd.find(messageID) != messagesRcvd.end();
}

bool AID::isInsideROI(MessageInfoEntry* info) {
    return info->messageOriginPosition.distance(curPosition) < info->messageROI;
}

bool AID::isMessageAlive(MessageInfoEntry* info) {
    return simTime() < info->messageOriginTime + info->messageTTL;
}

WaveShortMessage* AID::createDataMsg(MessageInfoEntry* info) {
    WaveShortMessage* wsm = prepareWSM("data", dataLengthBits, type_SCH, dataPriority, 0, info->messageID);

    DataMessage* msg = new DataMessage("data");

    msg->setMessageOriginPosition(info->messageOriginPosition);
    msg->setMessageROI(info->messageROI);
    msg->setMessageOriginTime(info->messageOriginTime);
    msg->setMessageTTL(info->messageTTL);
    msg->setHops(info->hops);

    wsm->setByteLength(info->messageLength);

    wsm->encapsulate(msg);

    return wsm;
}

void AID::addGPSError() {
    cRNG *rng = getRNG(9);
    double randomNumber, error;

    randomNumber = rng->doubleRand(); // Generate value in [0, 1)
    error = randomNumber * par("maxGPSError").doubleValue();

    if (randomNumber > 0.5) {
        curPosition.x += error;
        curPosition.y += error;
    } else {
        curPosition.x -= error;
        curPosition.y -= error;
    }
}

void AID::receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj) {
    Enter_Method_Silent();
    BaseWaveApplLayer::receiveSignal(source, signalID, obj);

    if (signalID == mobilityStateChangedSignal) {
        addGPSError();
    }
}

AID::~AID() {
    for (std::map<int, MessageInfoEntry*>::iterator i = messagesRcvd.begin(); i != messagesRcvd.end(); i++) {
        MessageInfoEntry* info = i->second;

        cancelAndDelete(info->broadcastTimer);
    }
    cancelAndDelete(dataRateTimer);
}
