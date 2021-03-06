package anfidissemination.application.routing.aid;
import org.car2x.veins.base.modules.IBaseApplLayer;

//
// WAVE application layer base class.
//
// @author David Eckhoff
//
// @see BaseWaveApplLayer
// @see Nic80211p
// @see Mac1609_4
// @see PhyLayer80211p
//
simple AID like IBaseApplLayer
{
    parameters:
        @statistic[duplicatedMessages](record=sum);
        @statistic[messagesTransmitted](record=sum);
        @statistic[messagesReceived](record=sum);
        @statistic[ttlDrop](record=sum);
        @statistic[aidDrop](record=sum);
        @statistic[messageReceivedHopCount](record=sum);
        @statistic[delay](record=sum);
        
        int ttl = default(5);
        
        bool debug = default(false); //whether to print debug output
        int headerLength = default(88bit) @unit(bit); //header length of the application
        
        double tau_max = default(0.1);

        bool sendBeacons = default(false); //tell the applayer to periodically send beacons
        int beaconLengthBits = default(256bit) @unit(bit); //the length of a beacon packet
        int beaconPriority = default(3); //the access category of the beacon messages
        volatile double beaconInterval = default(1s) @unit(s); //the intervall between 2 beacon messages

        double maxOffset = default(0s) @unit(s); //the maximum delay of messages sent down to avoid synchronous channel access
        bool sendData = default(false); //whether this applayer should send data
        int dataLengthBits = default(1024bit) @unit(bit); //the length of a data packet
        bool dataOnSch = default(true); //tells the applayer whether to use a service channel for datapackets or the control channel
        int dataPriority = default(3); //the access category for data packets

    gates:
        input lowerLayerIn; // from mac layer
        output lowerLayerOut; // to mac layer
        input lowerControlIn;
        output lowerControlOut;
}
