function [] = plot_histogram( titleText, data )
figure();

histogram(data);

title(titleText);

end

