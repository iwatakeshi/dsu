function compare(n, f1, f2, plot_title)
%COMPARE Summary of this function goes here
%   Detailed explanation goes here
plot(n, f1(n), n, f2(n), 'LineWidth', 2);
f1_name = func2str(f1);
f2_name = func2str(f2);

legend(f1_name, f2_name);
switch nargin
    case 4
        title(plot_title);
    otherwise
        title(strcat(f1_name, " vs. ", f2_name));
end