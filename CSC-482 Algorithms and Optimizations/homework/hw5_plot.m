n  = [1000, 2000, 4000, 8000, 16000, 32000];
brute_force = [0.336962, 2.74403, 21.9145, 173.1, 1387.35, 11119.2];
enhanced = [0.00269, 0.011959, 0.042832, 0.170507, 0.584651, 2.10087];


figure(1)
plot(n, brute_force, '-o', n, enhanced, '-o');
lgd = legend('Zero Triple Sum (Brute Force)', 'Zero Triple Sum (Enhanced)');
lgd.Location = 'NorthWest';
figure(2)
loglog(n, brute_force, '-o', n, enhanced, '-o');
lgd = legend('Zero Triple Sum (Brute Force)', 'Zero Triple Sum (Enhanced)');
lgd.Location = 'NorthWest';


slope = @(x1, y1, x2, y2) (log(y2) - log(y1)) / (log(x2) - log(x1));

disp("Slope for Zero-Triple-Sum (Brute force)");
disp(round(slope(n(1), brute_force(1), n(2), brute_force(2))));

disp("Slope for Zero-Triple-Sum (Enhanced)");
disp(round(slope(n(1), enhanced(1), n(2), enhanced(2))));
