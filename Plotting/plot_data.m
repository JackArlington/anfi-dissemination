close all;

% import data
[floodingName, floodingValue] = importfile('data/Flooding-0.sca');
[aidName, aidValue] = importfile('data/AID-0.sca');

% filter data for AID
aidMessagesTransmitted = aidValue(filter_data(aidName, 'messagesTransmitted:sum'));
aidMessagesReceived = aidValue(filter_data(aidName, 'messagesReceived:sum'));
aidDelay = aidValue(filter_data(aidName, 'delay:sum'));
aidHopCount = aidValue(filter_data(aidName, 'messageReceivedHopCount:sum'));
aidDuplicatedMessages = aidValue(filter_data(aidName, 'duplicatedMessages:sum'));
aidCarsReached = aidValue(filter_data(aidName, 'carReached:sum'));

% filter data for Flooding
floodingMessagesTransmitted = floodingValue(filter_data(floodingName, 'messagesTransmitted:sum'));
floodingMessagesReceived = floodingValue(filter_data(floodingName, 'messagesReceived:sum'));
floodingDelay = floodingValue(filter_data(floodingName, 'delay:sum'));
floodingHopCount = floodingValue(filter_data(floodingName, 'messageReceivedHopCount:sum'));
floodingDuplicatedMessages = floodingValue(filter_data(floodingName, 'duplicatedMessages:sum'));
floodingCarsReached = floodingValue(filter_data(floodingName, 'carReached:sum'));

% filter 0 values
aidMessagesTransmitted = filter_zero_values(aidMessagesTransmitted);
aidMessagesReceived = filter_zero_values(aidMessagesReceived);
aidDelay = filter_zero_values(aidDelay);
aidHopCount = filter_zero_values(aidHopCount);
aidDuplicatedMessages = filter_zero_values(aidDuplicatedMessages);

% adjust delay
aidDelay = aidDelay - 300;

floodingMessagesTransmitted = filter_zero_values(floodingMessagesTransmitted);
floodingMessagesReceived = filter_zero_values(floodingMessagesReceived);
floodingDelay = filter_zero_values(floodingDelay);
floodingHopCount = filter_zero_values(floodingHopCount);
floodingDuplicatedMessages = filter_zero_values(floodingDuplicatedMessages);

floodingDelay = floodingDelay - 300;

% create AID plots
plot_histogram(sprintf('Messages transmitted (AID) - per node reached: %0.3f', aidCarsReached/sum(aidMessagesTransmitted)), 'number of messages transmitted', 'number of nodes', false, aidMessagesTransmitted);
plot_histogram('Messages received (AID)','number of messages received', 'number of nodes', false, aidMessagesReceived);
plot_histogram('Message delay (AID)', 'message delay (ms)', 'number of nodes', false, aidDelay);
plot_histogram(sprintf('Message hop count (AID). Total number of cars reached: %d', aidCarsReached), 'number of hops', 'number of nodes', true, aidHopCount);
plot_histogram('Duplicated messages (AID)','number of duplicated messages', 'number of nodes', false, aidDuplicatedMessages);

% create Flooding plots
plot_histogram(sprintf('Messages transmitted (Flooding) - per node reached: %0.3f', floodingCarsReached/sum(floodingMessagesTransmitted)),'number of messages transmitted', 'number of nodes', false, floodingMessagesTransmitted);
plot_histogram('Messages received (Flooding)','number of messages received', 'number of nodes', false, floodingMessagesReceived);
plot_histogram('Message delay (Flooding)', 'message delay (ms)', 'number of nodes', false,floodingDelay);
plot_histogram(sprintf('Message hop count (Flooding) - Total number of cars reached: %d', floodingCarsReached), 'number of hops', 'number of nodes', true, floodingHopCount);
plot_histogram('Duplicated messages (Flooding)', 'number of duplicated messages', 'number of nodes', false, floodingDuplicatedMessages);

save_plots();