function [] = plot_histogram( titleText, xLab, yLab, sum_up, data )
figure();

histogram(data, 'FaceColor', 'blue');

xlabel(xLab);
ylabel(yLab);

title(titleText);
end

