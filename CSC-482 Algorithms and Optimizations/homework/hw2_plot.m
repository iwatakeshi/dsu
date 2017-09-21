
% i. n! vs. e^n
%figure(1);
% compare(1:1, @factorial, @exp, "n! vs e^n");

%figure(2);
%compare(1:10, @factorial, @exp, "n! vs e^n");

%figure(3);
%compare(1:1000, @factorial, @exp, "n! vs e^n");

% ii. e^n vs. 100 * n^10 + 55555 * n^5

% figure(4);
% compare(1:2^5.3, @exp, @(n) 100 * n.^10 + 55555 * n.^5)
% 
% figure(5);
% compare(1:2^5.4, @exp, @(n) 100 * n.^10 + 55555 * n.^5)
% 
% figure(6);
% compare(1:2^5.45, @exp, @(n) 100 * n.^10 + 55555 * n.^5)

% iii. 0.001 * n^5 vs. 1000 * n^4 + 99999 * n^3 + 999999 * n^2 + 888888888

%figure(7);
% compare(1:2^19, @(n) 0.001 * n.^5, @(n) 1000 * n.^4 + 99999 * n.^3 + 999999 * n.^2 + 888888888)

%figure(8);
% compare(1:2^19.5, @(n) 0.001 * n.^5, @(n) 1000 * n.^4 + 99999 * n.^3 + 999999 * n.^2 + 888888888)

%figure(9);
% compare(0:0.5:2^20, @(n) 0.001 * n.^5, @(n) 1000 * n.^4 + 99999 * n.^3 + 999999 * n.^2 + 888888888)

% iv. (n^7 + n^5 + 50 * n^2) / (n^6 +99 * n^3 + 88 * n^2) vs. (n^4 + n^3 + 999999)/(n^2 + 40 * n + 1)

f1 = @(n) 1000 * ((n.^7 + n.^5 + 50 * n.^2) ./ (n.^6 + 99 * n.^3 + 88 * n.^2));
f2 = @(n) ((n.^4 + n.^3 + 999999) ./ (n.^2 + 40 * n + 1));

%figure(10);
% compare(1:2^5, f1, f2);

%figure(11);
% compare(1:2^10, f1, f2);

%figure(12);
% compare(1:2^11, f1, f2);

% v. n  vs. n * log2(n)

% figure(13);
% compare(0:2^2, @(n) n, @(n) n .* log2(n));
% 
% figure(14);
% compare(0:2^5, @(n) n, @(n) n .* log2(n));
% 
% figure(15);
% compare(0:2^18, @(n) n, @(n) n .* log2(n));

% vi. n  vs  1000000 * n * log2(n)
% f1 = @(n) n;
% f2 = @(n) 1000000 * n .* log2(n);

% compare(1:0.5:2^18, f1, f2, 'PlotMethod', 'plot');

% vii. log2(n)  vs.  ln(n)  vs log10(n)
% compare2(0:0.5:2^10, @(n) log2(n), @(n) log(n), @(n) log10(n));

% viii. log2(n) vs log2(log2(n^5))
% compare(1:0.5:2^4, @(n) log2(n), @(n) log2(log2(n.^5)));
% compare(1:0.5:2^5, @(n) log2(n), @(n) log2(log2(n.^5)));

% ix. n^1.5 vs. 1000 *n * log2(n)

% compare(1:0.5:2^3, @(n) n.^5, @(n) 1000 * n .* log2(n));
% compare(1:0.5:2^4, @(n) n.^5, @(n) 1000 * n .* log2(n));

% x. n^.5 vs 99999 * log2(n)
% compare(1:0.01:2, @(n) n.^5, @(n) log2(n));

% xi. n.^(0.2) vs 99 * log2(n)
compare(1:0.01:2^18, @(n) n.^(0.2), @(n) 99 * log2(n));
