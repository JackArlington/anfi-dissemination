function [] = save_plots( )
h = get(0,'children');
h = sort(h);
for i=1:length(h)
  fig = h(i);
  titleElement = get(get(fig, 'children'), 'Title');
  titleText = get(titleElement, 'String');
  titleText = strrep(titleText, '.', '');
  titleText = strrep(titleText, ':', '');
  name = ['resultPlots/' titleText];
  saveas(h(i), name, 'fig');
  fig.Units = 'centimeters';
  pos = fig.Position;
  fig.PaperUnits = 'centimeters';
  width = pos(3);
  height = pos(4);
  fig.PaperPositionMode = 'manual';
  fig.PaperSize = [width height];
  fig.PaperPosition = [0 0 pos(3) pos(4)];
  print(fig, '-bestfit', name, '-dpdf');
  print(fig, name, '-dpng');
end
end

