close all;

[name, value] = importfile('data/scalar.sca');

messagesTransmitted = value(filter_data(name, 'messagesTransmitted:sum'));
messagesReceived = value(filter_data(name, 'messagesReceived:sum'));
totalTime = value(filter_data(name, 'totalTime'));

plot_histogram('Messages transmitted', messagesTransmitted);
plot_histogram('Messages received', messagesReceived);
plot_histogram('Total time', totalTime);

save_plots();