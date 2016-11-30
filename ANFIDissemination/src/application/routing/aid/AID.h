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

#ifndef AID_H_
#define AID_H_

#include <map>
#include <BaseApplLayer.h>
#include <Consts80211p.h>
//#include <WaveShortMessage_m.h>
#include <FloodingMessage_m.h>
#include "base/connectionManager/ChannelAccess.h"
#include <WaveAppToMac1609_4Interface.h>

#include "modules/mobility/traci/TraCIMobility.h"


using Veins::TraCIMobility;
using Veins::AnnotationManager;

#ifndef DBG
#define DBG EV
#endif

#define PACKET_HISTORY_LENGTH 10

class AID : public BaseApplLayer  {
public:
    AID();
    virtual ~AID();

    virtual void initialize(int stage);
    virtual void finish();

    virtual  void receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj);

    enum WaveApplMessageKinds {
        SERVICE_PROVIDER = LAST_BASE_APPL_MESSAGE_KIND,
        SEND_BEACON_EVT, GENERATE_MESSAGE
    };

protected:

    TraCIMobility* traci;
    AnnotationManager* annotations;

    static const simsignalwrap_t mobilityStateChangedSignal;

    /** @brief handle messages from below */
    virtual void handleLowerMsg(cMessage* msg);
    /** @brief handle self messages */
    virtual void handleSelfMsg(cMessage* msg);

    virtual FloodingMessage* prepareWSM(std::string name, int dataLengthBits, t_channel channel, int priority, int rcvId, int serial=0);
    virtual bool sendWSM(FloodingMessage* wsm);

    virtual void handlePositionUpdate(cObject* obj);

    virtual FloodingMessage* generateMessage();

protected:
    int beaconLengthBits;
    int beaconPriority;
    bool sendData;
    bool sendBeacons;
    simtime_t individualOffset;
    int dataLengthBits;
    bool dataOnSch;
    int dataPriority;
    Coord curPosition;
    int mySCH;
    int myId;

    cMessage* sendBeaconEvt;
    cMessage* generateMessageEvt;

    WaveAppToMac1609_4Interface* myMac;

private:
    int packetHistory[PACKET_HISTORY_LENGTH];

public:
    simsignal_t duplicatedMessages; // Indicate the number of duplicate messages received by a vehicle
    simsignal_t messagesTransmitted; // Indicate the number of messages transmitted by a vehicle
    simsignal_t messagesReceived; // Indicate whether the message was received or not
    simsignal_t retransmissionInhibited;
};

#endif /* AID_H_ */