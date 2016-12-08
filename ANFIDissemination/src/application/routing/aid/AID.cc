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

const simsignalwrap_t AID::mobilityStateChangedSignal = simsignalwrap_t(MIXIM_SIGNAL_MOBILITY_CHANGE_NAME);

using Veins::TraCIMobilityAccess;
using Veins::AnnotationManagerAccess;

Define_Module(AID);

AID::AID() {
    // TODO Auto-generated constructor stub

}

AID::~AID() {
    // TODO Auto-generated destructor stub
}

void AID::initialize(int stage) {
    BaseApplLayer::initialize(stage);

    if (stage==0) {
        myMac = FindModule<WaveAppToMac1609_4Interface*>::findSubModule(getParentModule());
        assert(myMac);

        myId = getParentModule()->getIndex();

        duplicatedMessages = registerSignal("duplicatedMessages");
        messagesTransmitted = registerSignal("messagesTransmitted");
        messagesReceived = registerSignal("messagesReceived");
        ttlDrop = registerSignal("ttlDrop");
        aidDrop = registerSignal("aidDrop");
        messageReceivedHopCount = registerSignal("messageReceivedHopCount");
        carCreated = registerSignal("carCreated");
        carReached = registerSignal("carReached");

        delay = registerSignal("delay");
        emit(carCreated, 1);

        traci = TraCIMobilityAccess().get(getParentModule());
        annotations = AnnotationManagerAccess().getIfExists();
        ASSERT(annotations);

        headerLength = par("headerLength").longValue();
        double maxOffset = par("maxOffset").doubleValue();
        beaconLengthBits = par("beaconLengthBits").longValue();
        beaconPriority = par("beaconPriority").longValue();

        sendData = par("sendData").boolValue();
        dataLengthBits = par("dataLengthBits").longValue();

        //simulate asynchronous channel access
        double offSet = dblrand() * (par("beaconInterval").doubleValue()/2);
        offSet = offSet + floor(offSet/0.050)*0.050;
        individualOffset = dblrand() * maxOffset;

        findHost()->subscribe(mobilityStateChangedSignal, this);

        generateMessageEvt = new cMessage("generate Message", GENERATE_MESSAGE);

        if(myId == 218) { // vehicle 218 is in the middle of the simulation scenario at 300s
            scheduleAt(simTime()+3.0, generateMessageEvt); // simTime has the current time + 10s as the shedule is absolute send message after 10s of warmup
        }

    }
}

FloodingMessage*  AID::prepareWSM(std::string name, int lengthBits, t_channel channel, int priority, int rcvId, int serial) {
    FloodingMessage* flm =      new FloodingMessage(name.c_str());
    flm->addBitLength(headerLength);
    flm->addBitLength(lengthBits);

    switch (channel) {
        case type_SCH: flm->setChannelNumber(Channels::SCH1); break; //will be rewritten at Mac1609_4 to actual Service Channel. This is just so no controlInfo is needed
        case type_CCH: flm->setChannelNumber(Channels::CCH); break;
    }
    flm->setPsid(0);
    flm->setPriority(priority);
    flm->setWsmVersion(1);
    flm->setTimestamp(simTime());
    flm->setSenderAddress(myId);
    flm->setRecipientAddress(rcvId);
    flm->setSenderPos(curPosition);
    flm->setSerial(serial);

    if (name == "beacon") {
        DBG << "Creating Beacon with Priority " << priority << " at Applayer at " << flm->getTimestamp() << std::endl;
    }
    if (name == "data") {
        DBG << "Creating Data with Priority " << priority << " at Applayer at " << flm->getTimestamp() << std::endl;
    }

    return flm;
}

void AID::receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj) {
    Enter_Method_Silent();
    if (signalID == mobilityStateChangedSignal) {
        handlePositionUpdate(obj);
    }
}

void AID::handlePositionUpdate(cObject* obj) {
    ChannelMobilityPtrType const mobility = check_and_cast<ChannelMobilityPtrType>(obj);
    curPosition = mobility->getCurrentPosition();
}

void AID::handleLowerMsg(cMessage* msg) {

    FloodingMessage* flm = dynamic_cast<FloodingMessage*>(msg);
    ASSERT(flm);

    emit(messagesReceived, 1);

    if(!carWasReached){
        carWasReached = true;
        emit(carReached,1);
        emit(delay, (flm->getArrivalTime()-flm->getSent()).dbl());
        emit(messageReceivedHopCount, flm->getHopCount());
    }

    if(tmpMsg == nullptr){
        // S1
        tmpMsg = flm;
        tmpMsg->setHopCount(tmpMsg->getHopCount()+1);
        s = 0;
        c = 0;
        ta = simTime();

        // S2
        tau = uniform(0, par("tau_max").doubleValue());

        transmittMessageEvt = new cMessage("transmit Message", TRANSMISSION_DELAY);

        scheduleAt(ta + tau, transmittMessageEvt);

    } else {
        emit(duplicatedMessages,1);
        tb = simTime();
        // S2.2
        c++;
        l.push_back((tb-ta).dbl());
    }
}

void AID::handleSelfMsg(cMessage* msg) {
    switch (msg->getKind()) {
        case GENERATE_MESSAGE: {
            sendWSM(generateMessage());
            break;
        }
        case TRANSMISSION_DELAY: {
            if(c > 0){
                // S4
                s=0;
                for (it=l.begin(); it<l.end(); it++) {
                    if((tau/c)-*it>0){
                        s--;
                    } else {
                        s++;
                    }
                }
                // S4.2
                if(s>10){
                    if(sendWSM(tmpMsg)) {
                        traci->commandSetColor(Veins::TraCIColor::fromTkColor("white"));
                    }
                } else {
                    // drop rebroadcast
                    emit(aidDrop, 1);
                }
            } else {
                // S3
                if(sendWSM(tmpMsg)) {
                    traci->commandSetColor(Veins::TraCIColor::fromTkColor("white"));
                }
            }
            l.clear();
            tmpMsg = nullptr;
            break;
        }
        default: {
            if (msg)
                DBG << "APP: Error: Got Self Message of unknown kind! Name: " << msg->getName() << endl;
            break;
        }
    }
}

bool AID::sendWSM(FloodingMessage* wsm) {

    wsm->setTtl(wsm->getTtl()-1);

    if(wsm->getTtl()>0) {
        sendDelayedDown(wsm,individualOffset);
        emit(messagesTransmitted, 1);
        return true;
    } else {
        emit(ttlDrop, 1);
        delete wsm;
        return false;
    }
}

void AID::finish() {
    findHost()->unsubscribe(mobilityStateChangedSignal, this);
}

FloodingMessage* AID::generateMessage() {

    FloodingMessage* flm = prepareWSM("flm", dataLengthBits, type_CCH, beaconPriority, 0, -1);
    flm->setMsgId(intuniform(0, 1000));
    traci->commandSetColor(Veins::TraCIColor::fromTkColor("violet"));
    flm->setTtl(par("ttl"));

    return flm;
}

