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

#ifndef __AID_AID_H_
#define __AID_AID_H_

#include "BaseWaveApplLayer.h"
#include "WaveShortMessage_m.h"
#include "DataMessage_m.h"
#include "TraCIMobility.h"
#include <algorithm>

using Veins::TraCIMobility;

/**
 * TODO - Generated class
 */
class AID : public BaseWaveApplLayer {

private:
    struct MessageInfoEntry {
        int messageID; // Message unique ID

        Coord messageOriginPosition; // Message origin
        double messageROI; // Region of Interest in meters
        simtime_t messageOriginTime; // Time of message inception at source host
        simtime_t messageTTL; // Message's time-to-live
        int hops; // Message's number of hops

        simtime_t receptionTime;
        int messageLength;

        int c;
        simtime_t lastReceptionTime;
        std::vector<simtime_t> deltaTimes;

        cMessage* broadcastTimer; // Self-message for broadcast suppression
    };

    enum AIDMessageKinds {
        BROADCAST_TIMEOUT = SEND_BEACON_EVT + 1, // Timer used to control the wait time for vehicles. When it fires, then send message
        SEND_DATA,
    };

protected:
    static const simsignalwrap_t mobilityStateChangedSignal;

    TraCIMobility* traci;

    cMessage* dataRateTimer;

    double datarate;

    std::map<int, MessageInfoEntry*> messagesRcvd;

    std::list<int> outputQueue;

    virtual void initialize(int);
    virtual void finish();
    virtual void handleSelfMsg(cMessage* msg);
    virtual void onBeacon(WaveShortMessage* wsm);
    virtual void onData(WaveShortMessage* wsm);

    virtual void addMessageToOutputQueue(MessageInfoEntry* info);
    virtual void sendData();

    virtual bool isDuplicateMsg(int messageID);
    virtual bool isInsideROI(MessageInfoEntry* info);
    virtual bool isMessageAlive(MessageInfoEntry* info);
    virtual WaveShortMessage* createDataMsg(MessageInfoEntry* info);

    virtual void addGPSError();
    virtual void receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj);

public:
    simsignal_t duplicatedMessages; // Indicate the number of duplicate messages received by a vehicle
    simsignal_t messagesTransmitted; // Indicate the number of messages transmitted by a vehicle
    simsignal_t messagesReceived; // Indicate whether the message was received or not

    virtual ~AID();
};

#endif
