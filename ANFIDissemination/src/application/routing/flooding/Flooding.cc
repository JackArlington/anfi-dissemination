#include "Flooding.h"

const simsignalwrap_t Flooding::mobilityStateChangedSignal = simsignalwrap_t(MIXIM_SIGNAL_MOBILITY_CHANGE_NAME);

using Veins::TraCIMobilityAccess;
using Veins::AnnotationManagerAccess;

Define_Module(Flooding);

void Flooding::initialize(int stage) {
	BaseApplLayer::initialize(stage);

	if (stage==0) {
		myMac = FindModule<WaveAppToMac1609_4Interface*>::findSubModule(getParentModule());
		assert(myMac);

		myId = getParentModule()->getIndex();

        duplicatedMessages = registerSignal("duplicatedMessages");
        messagesTransmitted = registerSignal("messagesTransmitted");
        messagesReceived = registerSignal("messagesReceived");
        floodingDrop = registerSignal("floodingDrop");
        messageReceivedHopCount = registerSignal("messageReceivedHopCount");
        ttlDrop = registerSignal("ttlDrop");
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
            scheduleAt(simTime()+10.0, generateMessageEvt); // simTime has the current time + 10s as the shedule is absolute send message after 10s of warmup
        }

	}
}

FloodingMessage*  Flooding::prepareWSM(std::string name, int lengthBits, t_channel channel, int priority, int rcvId, int serial) {
    FloodingMessage* flm =		new FloodingMessage(name.c_str());
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

void Flooding::receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj) {
	Enter_Method_Silent();
	if (signalID == mobilityStateChangedSignal) {
		handlePositionUpdate(obj);
	}
}

void Flooding::handlePositionUpdate(cObject* obj) {
	ChannelMobilityPtrType const mobility = check_and_cast<ChannelMobilityPtrType>(obj);
	curPosition = mobility->getCurrentPosition();
}

void Flooding::handleLowerMsg(cMessage* msg) {

	FloodingMessage* flm = dynamic_cast<FloodingMessage*>(msg);
	ASSERT(flm);

	emit(messagesReceived, 1);
    if(sendWSM(flm)) {
        traci->commandSetColor(Veins::TraCIColor::fromTkColor("white"));
    }

}

void Flooding::handleSelfMsg(cMessage* msg) {
	switch (msg->getKind()) {
		case GENERATE_MESSAGE: {
			sendWSM(generateMessage());
			break;
		}
		default: {
			if (msg)
				DBG << "APP: Error: Got Self Message of unknown kind! Name: " << msg->getName() << endl;
			break;
		}
	}
}

bool Flooding::sendWSM(FloodingMessage* wsm) {
    static int packetHistoryIndex;
    bool packetSent = false;

    for(int i=0; i<PACKET_HISTORY_LENGTH; i++){
        if(packetHistory[i] == wsm->getMsgId()){
            emit(duplicatedMessages, 1);
            packetSent = true;
        }
    }

    if(packetHistoryIndex >= PACKET_HISTORY_LENGTH){
        packetHistoryIndex = 0;
    }


    wsm->setTtl(wsm->getTtl()-1);
    wsm->setHopCount(wsm->getHopCount()+1);

    if(!packetSent){
        emit(messageReceivedHopCount, wsm->getHopCount()-1);

        emit(delay,(wsm->getArrivalTime()-wsm->getSent()).dbl());

        emit(carReached,1);
    }

    if(!packetSent && wsm->getTtl()>0) {
 //       cMessage *copy = (cMessage *)wsm->dup();
        packetHistory[packetHistoryIndex++] = wsm->getMsgId();
        sendDelayedDown(wsm,individualOffset);

        emit(messagesTransmitted, 1);
        return true;
    } else {
        if(packetSent){
            emit(floodingDrop, 1);
        }
        if(wsm->getTtl()<0){
            emit(ttlDrop,1);
        }
        delete wsm;
        return false;
    }
}

void Flooding::finish() {
	findHost()->unsubscribe(mobilityStateChangedSignal, this);
}

FloodingMessage* Flooding::generateMessage() {

    FloodingMessage* flm = prepareWSM("flm", dataLengthBits, type_CCH, beaconPriority, 0, -1);
    flm->setMsgId(intuniform(0, 1000));
    traci->commandSetColor(Veins::TraCIColor::fromTkColor("violet"));
    flm->setTtl(par("ttl"));

    return flm;
}

Flooding::~Flooding() {

}
