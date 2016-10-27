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

#include "RSUApplication.h"

Define_Module(RSUApplication);

const simsignalwrap_t RSUApplication::mobilityStateChangedSignal = simsignalwrap_t(MIXIM_SIGNAL_MOBILITY_CHANGE_NAME);

void RSUApplication::initialize(int stage) {
    BaseWaveApplLayer::initialize(stage);

    if (stage == 0) {
        if (par("sendData").boolValue()) {
            datarate = par("datarate").doubleValue();
            startDissemination = new cMessage("start dissemination", START_DISSEMINATION);
            scheduleAt(par("startDataProductionTime").doubleValue(), startDissemination);
        }
    }
}

void RSUApplication::finish() {
    BaseWaveApplLayer::finish();

    std::ofstream log;
    std::ostringstream o;

    o << "./results/" << par("log_traffic").longValue() << "-" << par("log_replication").longValue() << "-sender";
    log.open(o.str().c_str());

    for (std::map<simtime_t, MessageEntryInfo*>::iterator i = loggingInfo.begin(); i != loggingInfo.end(); i++) {
        simtime_t time = i->first;
        MessageEntryInfo* videoInfo = i->second;

        //tempo \t id n�mero \t udp tamanho
        log << time << " " << "id " << videoInfo->ID << " " << "udp " << videoInfo->length << endl;
    }
}

RSUApplication::~RSUApplication() {}

void RSUApplication::handleSelfMsg(cMessage* msg) {
    switch (msg->getKind()) {
        case START_DISSEMINATION: {
            readDataFromFile();
            sendDataTimer = new cMessage("Send data", SEND_DATA);
            scheduleAt(simTime(), sendDataTimer);
            delete msg;

            break;
        }

        case SEND_DATA: {
            sendData();

            break;
        }

        default: {
            if (msg)
                EV << "Error: Got Self Message of unknown kind! Name: " << msg->getName() << endl;
            break;
        }
    }
}

void RSUApplication::onBeacon(WaveShortMessage* wsm) {}

void RSUApplication::onData(WaveShortMessage* wsm) {}

void RSUApplication::sendData() {

    //double delay = 0.0;

    //for (int i = 0; i < 10; i++) {

        if (outputQueue.size() != 0) {
            MessageEntryInfo* videoInfo = outputQueue.front();
            outputQueue.pop_front();

            WaveShortMessage* wsm = prepareWSM("data", dataLengthBits, type_SCH, dataPriority, 0, videoInfo->ID);

            // Send first message
            DataMessage* dataMsg = new DataMessage("data");
            dataMsg->setHops(0);

            dataMsg->setMessageOriginPosition(curPosition);
            dataMsg->setMessageROI(par("dataROI").doubleValue());
            dataMsg->setMessageOriginTime(simTime());
            dataMsg->setMessageTTL(par("dataTTL"));

            wsm->setByteLength(videoInfo->length);

            wsm->encapsulate(dataMsg);
            sendWSM(wsm);

            loggingInfo[simTime()] = videoInfo;

            double nextPktTime = wsm->getBitLength() / datarate;
            scheduleAt(simTime() + nextPktTime, sendDataTimer);
        } else {
            cancelAndDelete(sendDataTimer);
        }
        //delay += 0.025;
    //}
}

void RSUApplication::readDataFromFile() {
    std::ifstream sender_trace_file("sender_trace_packets");
    std::string line;

    //int ID;
    //char type;
    //double time;
    //int length;
    //int unknown1;
    //int unknown2;

    /*while (sender_trace_file >> ID >> type >> time >> length >> unknown1 >> unknown2) {
        MessageEntryInfo* videoInfo = new MessageEntryInfo;
        videoInfo->ID = ID;
        videoInfo->length = length;

        outputQueue.push_back(videoInfo);
    }*/

    MessageEntryInfo* videoInfo = new MessageEntryInfo;
    videoInfo->ID = 1;
    videoInfo->length = 2048;

    outputQueue.push_back(videoInfo);
}


void RSUApplication::receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj) {
    Enter_Method_Silent();
    BaseWaveApplLayer::receiveSignal(source, signalID, obj);
}
