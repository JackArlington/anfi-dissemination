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

#include "Flooding.h"

using namespace Veins;

Define_Module(Flooding);

const simsignalwrap_t Flooding::mobilityStateChangedSignal = simsignalwrap_t(MIXIM_SIGNAL_MOBILITY_CHANGE_NAME);

void Flooding::initialize(int stage)
{
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

void Flooding::finish() {
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

void Flooding::handleSelfMsg(cMessage* msg) {
    switch (msg->getKind()) {
        case SEND_DATA: {
            sendData();

            break;
        }

        default: {
            if (msg)
                EV << "Flooding - Error: Got Self Message of unknown kind! Name: " << msg->getName() << endl;
            break;
        }
    }
}

void Flooding::onBeacon(WaveShortMessage* wsm) {}

void Flooding::onData(WaveShortMessage* wsm) {
    MessageInfoEntry* info = extractMsgInfo(wsm);

    if (!isInsideROI(info) || !isMessageAlive(info)) {
        return;
    }

    if (!isDuplicateMsg(info->messageID)) {
        // Store message info
        messagesRcvd[info->messageID] = info;
        addMessageToOutputQueue(info);
        emit(messagesReceived, 1);
    } else {
        emit(duplicatedMessages, 1);
    }
}

Flooding::MessageInfoEntry* Flooding::extractMsgInfo(WaveShortMessage* wsm) {
    if (isDuplicateMsg(wsm->getSerial())) {
        return messagesRcvd[wsm->getSerial()];
    }
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

    delete dataMsg;

    return info;
}

void Flooding::addMessageToOutputQueue(MessageInfoEntry* info) {
    if (std::find(outputQueue.begin(), outputQueue.end(), info->messageID) == outputQueue.end()) {
        outputQueue.push_back(info->messageID);
        if (!dataRateTimer->isScheduled()) {
            scheduleAt(simTime(), dataRateTimer);
        }
    }
}

void Flooding::sendData() {
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

bool Flooding::isDuplicateMsg(int messageID) {
    return messagesRcvd.find(messageID) != messagesRcvd.end();
}

bool Flooding::isInsideROI(MessageInfoEntry* info) {
    return info->messageOriginPosition.distance(curPosition) < info->messageROI;
}

bool Flooding::isMessageAlive(MessageInfoEntry* info) {
    return simTime() < info->messageOriginTime + info->messageTTL;
}

WaveShortMessage* Flooding::createDataMsg(MessageInfoEntry* info) {
    WaveShortMessage* wsm = prepareWSM("data", dataLengthBits, type_CCH, dataPriority, 0, info->messageID);

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

void Flooding::receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj) {
    Enter_Method_Silent();
    BaseWaveApplLayer::receiveSignal(source, signalID, obj);
}

Flooding::~Flooding() {
    cancelAndDelete(dataRateTimer);
}
