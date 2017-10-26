% QuickSort (N: Random)

qs_random = [
%  N         T1       T2       T3       T4       T5       T6       T7       T8       T9      T10
  2000 	  0.000263 0.000388 0.000362 0.000274 0.000251 0.000262 0.000262 0.000281 0.000334 0.000262
  4000 	  0.000583 0.001531 0.000662 0.000629 0.000576 0.000584 0.000568 0.000594 0.005449 0.005206
  8000 	  0.001247 0.001304 0.001224 0.001269 0.001562 0.001286 0.001573 0.002612 0.002783 0.002822
  16000 	0.003503 0.003666 0.002662 0.002747 0.004270 0.002583 0.002795 0.002671 0.002710 0.002613
  32000 	0.005691 0.006538 0.006266 0.007824 0.007074 0.007206 0.006072 0.006142 0.006286 0.005718
  64000 	0.013780 0.013665 0.013888 0.012444 0.012438 0.012724 0.012523 0.012997 0.012303 0.012167
  128000 	0.028877 0.028706 0.028196 0.026599 0.027560 0.025960 0.026201 0.025697 0.026532 0.025977
  256000 	0.060560 0.061877 0.068750 0.055192 0.055451 0.055426 0.057371 0.057539 0.055079 0.057358
];

qs_random_avg = sum(qs_random(1:8, 2:11), 2) ./ 10;

% Quicksort (N: Random, Fn: Random)

qs_random_random = [
%  N        T1       T2       T3       T4       T5       T6       T7       T8       T9      T10
  2000 	 0.000338 0.000360 0.000349 0.000384 0.000466 0.003429 0.000395 0.003899 0.000389 0.000348
  4000 	 0.001125 0.000732 0.000989 0.000729 0.000861 0.000870 0.000734 0.000702 0.000799 0.000722
  8000 	 0.001823 0.001668 0.001892 0.001594 0.001597 0.004157 0.001748 0.001601 0.001534 0.001556
  16000  0.003390 0.003726 0.003396 0.003395 0.003249 0.003239 0.003392 0.003793 0.003331 0.003895
  32000  0.008273 0.007185 0.007361 0.007172 0.007168 0.007150 0.007711 0.007310 0.007740 0.007877
  64000  0.014835 0.015030 0.014904 0.014826 0.015249 0.014485 0.014794 0.014732 0.014386 0.015988
  128000 0.031628 0.031807 0.030850 0.031280 0.031118 0.031911 0.031025 0.032238 0.030286 0.031296
  256000 0.067816 0.068790 0.065330 0.065543 0.070341 0.068415 0.066163 0.066659 0.065280 0.066190
];

qs_random_random_avg = sum(qs_random_random(1:8, 2:11), 2) ./ 10;

plot(qs_random(:,1), qs_random_avg, '-o', qs_random_random(:,1), qs_random_random_avg, '-o');

% Quicksort (N: Ascending) 

qs_ascending = [
%  N        T1        T2        T3        T4        T5        T6        T7        T8        T9       T10
  2000 	 0.005770  0.004864  0.004615  0.012515  0.004714  0.009696  0.004992  0.010193  0.008258  0.008002
  4000 	 0.021576  0.020422  0.028876  0.026518  0.020535  0.021509  0.020150  0.021050  0.021117  0.031633
  8000 	 0.079727  0.089404  0.087644  0.079182  0.092130  0.094274  0.081257  0.081286  0.083823  0.085224
  16000  0.304528  0.314875  0.343507  0.343085  0.335932  0.345007  0.307268  0.312099  0.311550  0.318447
  32000  1.198024  1.230639  1.259273  1.232871  1.257666  1.261142  1.209532  1.212302  1.219920  1.229350
  64000  4.813198  4.948262  4.919311  5.066958  4.871870  4.847081  4.954938  4.819409  4.856087  4.935799
  128000 19.339023 19.489787 19.390403 19.388694 19.381678 19.318395 19.826248 19.406397 19.287023 19.484032
  256000 76.961617 76.908900 78.187914 76.946257 77.385098 79.346912 77.189295 77.460761 77.314520 77.285551
];

qs_ascending_avg = sum(qs_ascending(1:8, 2:11), 2) ./ 10;

% Quicksort (N: Ascending, Fn: Random)

qs_ascending_random = [
%  N        T1       T2       T3       T4       T5       T6       T7       T8       T9      T10
  2000 	 0.000190 0.000188 0.000242 0.000327 0.000205 0.000244 0.000188 0.000196 0.000193 0.000242
  4000 	 0.000416 0.000411 0.000464 0.000445 0.000420 0.000375 0.000388 0.000390 0.000398 0.000382
  8000 	 0.000853 0.000859 0.000817 0.000851 0.000840 0.000823 0.000826 0.000834 0.000811 0.000895
  16000  0.001735 0.001749 0.001717 0.001665 0.001781 0.002959 0.003473 0.002492 0.001760 0.001728
  32000  0.007484 0.003758 0.003586 0.003533 0.003559 0.005162 0.004028 0.004180 0.003506 0.008353
  64000  0.007023 0.009458 0.006900 0.008041 0.007159 0.007078 0.007708 0.007162 0.007213 0.007071
  128000 0.014762 0.016074 0.017170 0.017091 0.016993 0.014817 0.015076 0.014897 0.015273 0.014590
  256000 0.030457 0.030592 0.029902 0.030075 0.031473 0.030345 0.029722 0.030162 0.030376 0.029591
];

qs_ascending_random_avg = sum(qs_ascending_random(1:8, 2:11), 2) ./ 10;

plot(qs_ascending(:,1), qs_ascending_avg, '-o', qs_ascending_random(:,1), qs_ascending_random_avg, '-o');

% Quicksort (N: Descending)

qs_descending = [
%  N        T1        T2        T3        T4        T5        T6        T7        T8        T9       T10
  2000 	 0.007769  0.034776  0.005332  0.014885  0.014987  0.013143  0.012401  0.006329  0.014947  0.004821
  4000 	 0.021481  0.032118  0.026766  0.023412  0.023137  0.024492  0.028271  0.021919  0.022569  0.028807
  8000 	 0.083680  0.083997  0.097037  0.092597  0.093198  0.084474  0.093910  0.088242  0.079307  0.082689
  16000  0.307156  0.472484  0.347515  0.350062  0.357415  0.342040  0.336840  0.333076  0.349560  0.328184
  32000  1.223824  1.366145  1.273209  1.306353  1.278358  1.287496  1.267257  1.259997  1.257185  1.238724
  64000  4.944253  5.059316  5.022058  5.020489  4.996877  4.980859  5.045541  4.958585  4.957576  4.971865
  128000 19.715038 20.576861 19.557931 19.637361 19.706244 19.668743 19.658541 19.680916 19.651894 19.750736
  256000 81.376618 80.460274 78.011458 78.438143 79.348494 77.997180 78.693753 78.498913 78.051350 78.277789
];

qs_descending_avg = sum(qs_descending(1:8, 2:11), 2) ./ 10;

% Quicksort (N: Descending, Fn: Random)

qs_descending_random = [
%  N        T1        T2        T3      T4      T5      T6        T7       T8       T9      T10
  2000   0.000208 0.001141 0.000232 0.000208 0.000214 0.000212 0.000209 0.000219 0.000208 0.000207
  4000   0.000433 0.000475 0.000418 0.000457 0.000451 0.000457 0.003387 0.000415 0.000452 0.000544
  8000   0.002324 0.000934 0.000860 0.000909 0.000969 0.000933 0.000949 0.000969 0.000923 0.000898
  16000  0.001878 0.002263 0.001767 0.001889 0.001838 0.001899 0.001798 0.001844 0.001877 0.005683
  32000  0.003680 0.004069 0.005384 0.006840 0.004389 0.010642 0.003671 0.003805 0.005416 0.003843
  64000  0.008195 0.007765 0.007813 0.007989 0.009064 0.007712 0.013458 0.008394 0.007781 0.007904
  128000 0.015391 0.018043 0.016132 0.015848 0.016164 0.017132 0.016640 0.015844 0.015282 0.017007
  256000 0.032579 0.032398 0.033552 0.033821 0.033974 0.032129 0.031537 0.035248 0.032360 0.033173
];

qs_descending_random_avg = sum(qs_descending_random(1:8, 2:11), 2) ./ 10;

plot(qs_descending(:,1), qs_descending_avg, '-o', qs_descending_random(:,1), qs_descending_random_avg, '-o');

% Quicksort (N: Shuffle)

qs_shuffle = [
%   S        T1        T2        T3      T4      T5      T6        T7       T8       T9      T10
  16000   0.164773 0.129399 0.095121 0.116495 0.144747 0.112543 0.074035 0.105518 0.165308 0.085529
  32000   0.066464 0.082257 0.056802 0.063500 0.061168 0.074377 0.058550 0.059730 0.088625 0.058032
  64000   0.070538 0.056049 0.073190 0.065703 0.049183 0.051546 0.053784 0.050411 0.060102 0.050957
  128000  0.051521 0.061889 0.065851 0.060330 0.057326 0.055816 0.050345 0.051730 0.061466 0.052496
  256000  0.055129 0.054756 0.064275 0.067384 0.064153 0.067908 0.054778 0.059083 0.063192 0.056337
  512000  0.067747 0.055091 0.058667 0.057009 0.068805 0.063253 0.068641 0.056194 0.057463 0.055662
  1024000 0.072184 0.072500 0.072297 0.055889 0.055445 0.056291 0.066940 0.065729 0.063292 0.055364
  2048000 0.056035 0.056711 0.083373 0.067286 0.072242 0.055264 0.056045 0.066109 0.076193 0.062499
];

qs_shuffle_avg = sum(qs_shuffle(1:8, 2:11), 2) ./ 10;

% Quicksort (N: Shuffle, Fn: Random)

qs_shuffle_random = [
%  S        T1        T2        T3      T4      T5      T6        T7       T8       T9      T10
  16000   0.085019 0.066112 0.071775 0.050913 0.051870 0.065676 0.078243 0.073179 0.050863 0.067904
  32000   0.080429 0.095305 0.065139 0.072255 0.055722 0.055507 0.056870 0.057332 0.053766 0.054693
  64000   0.063720 0.082388 0.071887 0.071988 0.076346 0.062384 0.065321 0.061906 0.061728 0.060485
  128000  0.073222 0.073343 0.104201 0.080567 0.094007 0.095546 0.090048 0.098772 0.071416 0.069939
  256000  0.079729 0.079622 0.079101 0.078996 0.095814 0.088747 0.097724 0.093049 0.077477 0.076969
  512000  0.080536 0.101491 0.080006 0.079520 0.080362 0.081914 0.098920 0.101507 0.089497 0.078500
  1024000 0.080190 0.099041 0.078561 0.103533 0.080211 0.080017 0.082399 0.082364 0.100626 0.084740
  2048000 0.082812 0.081019 0.080142 0.099579 0.091526 0.336014 0.097324 0.079779 0.079733 0.091317
];

qs_shuffle_random_avg = sum(qs_shuffle_random(1:8, 2:11), 2) ./ 10;

plot(qs_shuffle(:,1), qs_shuffle_avg, qs_shuffle_random(:,1), qs_shuffle_random_avg);

% plot all non-random quicksorts
plot(qs_random(:,1), qs_random_avg, '-o', ...
  qs_ascending(:,1), qs_ascending_avg, '-o', ...
  qs_descending(:,1), qs_descending_avg, '-o', ...
  qs_shuffle(:,1), qs_shuffle_avg, '-o');

% plot all random quicksorts
plot(qs_random_random(:,1), qs_random_random_avg, '-o', ...
  qs_ascending_random(:,1), qs_ascending_random_avg, '-o', ...
  qs_descending_random(:,1), qs_descending_random_avg, '-o', ...
  qs_shuffle_random(:,1), qs_shuffle_random_avg, '-o');

set(gca,'XTick',0:2048000);
set(gca,'YTick',0:1000);
