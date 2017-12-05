function compare2(n, f1, f2, f3, varargin)
%COMPARE Compares two functions with a given sets and displays a plot

% Get the function names
f1_name = func2str(f1);
f2_name = func2str(f2);
f3_name = func2str(f3);

% set parameters %
p = inputParser;

default_plot_method = 'plot';
expected_plot_method = { 'plot', 'loglog' };
default_title = strcat(f1_name, " vs. ", f2_name, ' vs. ', f3_name);
default_legend_location = 'best';
expected_legend_location = { ...
    'north', 'south', 'east', 'west', ...
    'northeast', 'northwest', 'southeast', 'southwest', ...
    'northoutside', 'southoutside', 'eastoutside', 'westoutside', ...
    'northeastoutside', 'northwestoutside', 'southeastoutside', 'southwestoutside', ...
    'best', 'bestoutside', 'none' ...
};

addParameter(p, 'Title', default_title);
addParameter(p, 'PlotMethod', default_plot_method, ...
                 @(x) any(validatestring(x,expected_plot_method)));
addParameter(p, 'LegendLocation',default_legend_location,...
                 @(x) any(validatestring(x,expected_legend_location)));

parse(p, varargin{:});


switch p.Results.PlotMethod
    case 'plot'
        plot(n, f1(n), n, f2(n), n, f3(n), 'LineWidth', 2);
    case 'loglog'
        loglog(n, f1(n), n, f2(n), n, f3(n), 'LineWidth', 2);
    otherwise
        plot(n, f1(n), n, f2(n), n, f3(n), 'LineWidth', 2);
end

ax = gca;
ax.XAxisLocation = 'origin';



% Set title
title(p.Results.Title);
% Set legend
lgd = legend(f1_name, f2_name, f3_name);
% Set legend location
lgd.Location = p.Results.LegendLocation;

end