#include "RSUApplication.h"

const simsignalwrap_t RSUApplication::mobilityStateChangedSignal = simsignalwrap_t(MIXIM_SIGNAL_MOBILITY_CHANGE_NAME);

using Veins::TraCIMobilityAccess;
using Veins::AnnotationManagerAccess;

Define_Module(RSUApplication);

void RSUApplication::initialize(int stage) {
	BaseApplLayer::initialize(stage);

	if (stage==0) {
		myMac = FindModule<WaveAppToMac1609_4Interface*>::findSubModule(getParentModule());
		assert(myMac);

		myId = getParentModule()->getIndex();

        duplicatedMessages = registerSignal("duplicatedMessages");
        messagesTransmitted = registerSignal("messagesTransmitted");
        messagesReceived = registerSignal("messagesReceived");

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

		scheduleAt(simTime()+10.0, generateMessageEvt); // simTime has the current time + 10s as the shedule is absolute send message after 10s of warmup

	}
}

FloodingMessage*  RSUApplication::prepareWSM(std::string name, int lengthBits, t_channel channel, int priority, int rcvId, int serial) {
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

void RSUApplication::receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj) {
	Enter_Method_Silent();
	if (signalID == mobilityStateChangedSignal) {
		handlePositionUpdate(obj);
	}
}

void RSUApplication::handlePositionUpdate(cObject* obj) {
	ChannelMobilityPtrType const mobility = check_and_cast<ChannelMobilityPtrType>(obj);
	curPosition = mobility->getCurrentPosition();
}

void RSUApplication::handleLowerMsg(cMessage* msg) {

	FloodingMessage* flm = dynamic_cast<FloodingMessage*>(msg);
	ASSERT(flm);

	flm->setTtl(flm->getTtl()-1);

	if(flm->getTtl()>0){
        if(sendWSM(flm)) {
            traci->commandSetColor(Veins::TraCIColor::fromTkColor("white"));
        }
	}
}

void RSUApplication::handleSelfMsg(cMessage* msg) {
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

bool RSUApplication::sendWSM(FloodingMessage* wsm) {

    if(true) {
        sendDelayedDown(wsm,individualOffset);
        emit(messagesTransmitted, 1);
        return true;
    } else {
        delete wsm;
        return false;
    }
}

void RSUApplication::finish() {
	findHost()->unsubscribe(mobilityStateChangedSignal, this);
}

FloodingMessage* RSUApplication::generateMessage() {

    FloodingMessage* flm = prepareWSM("flm", dataLengthBits, type_CCH, beaconPriority, 0, -1);
    flm->setMsgId(intuniform(0, 1000));
    traci->commandSetColor(Veins::TraCIColor::fromTkColor("violet"));
    flm->setTtl(par("ttl"));

    return flm;
}

RSUApplication::~RSUApplication() {

}
