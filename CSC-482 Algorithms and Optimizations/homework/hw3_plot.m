fib_recursive_name = 'Fibonacci (recursive)';
fib_recursive = [
    0
    0
    0
    0
    0
    0
    0
    0
    0
    0
    0
    0
    0
    0
    0
    0
    0
    0
    0
    0
    0
    0
    0
    0
    1
    2
    4
    7
    13
    21
    33
    64
    79
    123
    199
    315
    514
    819
    1324
    2144
    3501
    5567
    9054
    14616
    23411
    37889
    61402
    98952
    160636
    260094
    420805
    681264
    1097904
    1784808
    2891066
];

plot(1 : 55, fib_recursive, 'LineWidth', 2);
title(fib_recursive_name);

fib_looped_name = 'Fibonacci (non-recursive)';
fib_looped = [
    8.62e-06
    8.29e-06
    3.522e-05
    4.734e-05
    5.711e-05
    8.058e-05
    8.967e-05
    9.918e-05
    0.00011113
    0.00012115
    0.00013199
    0.00014167
    0.0001525
    0.00016429
    0.00017384
    0.00018391
    0.00019682
    0.00020645
    0.00021699
    0.00022813
    0.00024011
    0.0002502
    0.00026068
    0.00027083
    0.00028106
    0.00029252
    0.00030449
    0.00031474
    0.00032516
    0.0003369
    0.00034462
    0.00035848
    0.0003684
    0.00037708
    0.00040297
    0.00040545
    0.00041304
    0.00042379
    0.00043391
    0.00044218
    0.00045494
    0.00046474
    0.00047593
    0.00048523
    0.0004966
    0.00051102
    0.00051859
    0.00052992
    0.00053905
    0.00055292
    0.00055989
    0.00057181
    0.00058394
    0.00059465
    0.00061001
];

figure(2);
plot(1 : 55, fib_looped);
title(fib_looped_name);

fib_memoized_name = 'Fibonacci (cached)';
fib_memoized = [
    2.9e-05
    2.848e-05
    2.873e-05
    2.866e-05
    2.884e-05
    2.881e-05
    2.912e-05
    2.944e-05
    2.859e-05
    2.875e-05
    2.813e-05
    2.898e-05
    2.883e-05
    2.835e-05
    2.837e-05
    3.036e-05
    2.985e-05
    2.928e-05
    2.864e-05
    3.021e-05
    2.911e-05
    2.868e-05
    3.027e-05
    2.889e-05
    2.864e-05
    2.969e-05
    2.977e-05
    2.981e-05
    2.937e-05
    2.889e-05
    2.973e-05
    2.933e-05
    2.874e-05
    2.906e-05
    3.017e-05
    2.935e-05
    2.934e-05
    2.978e-05
    2.948e-05
    2.855e-05
    2.926e-05
    2.89e-05
    2.947e-05
    2.942e-05
    2.935e-05
    2.908e-05
    2.848e-05
    2.892e-05
    2.913e-05
    2.969e-05
    2.883e-05
    2.902e-05
    2.839e-05
    2.972e-05
    2.907e-05
];

figure(3);
plot(1 : 55, fib_memoized, 'LineWidth', 2);
title(fib_memoized_name);

fib_matrixed_name = 'Fibonacci (matrixed)';
fib_matrixed = [
    2.381e-05
    2.286e-05
    0.00019107
    0.00030163
    0.0003532
    0.00048244
    0.00049352
    0.00058749
    0.00051578
    0.00065623
    0.00064139
    0.00075016
    0.00064361
    0.00075126
    0.00075261
    0.00084844
    0.00067711
    0.00080225
    0.00080335
    0.00093982
    0.0007997
    0.00093871
    0.00094129
    0.00101798
    0.00079622
    0.00093852
    0.00093998
    0.00102386
    0.00096161
    0.0010216
    0.00102182
    0.00111372
    0.00084851
    0.00097161
    0.00097071
    0.00110293
    0.00097214
    0.00111164
    0.00110286
    0.00120403
    0.00096913
    0.00110827
    0.00111584
    0.00124539
    0.00115623
    0.001225
    0.00119251
    0.0012961
    0.00096405
    0.00109558
    0.0011003
    0.00119845
    0.00109894
    0.00119764
    0.00119957
];

figure(4);
plot(1 : 55, fib_matrixed, 'LineWidth', 2);
title(fib_matrixed_name);

x = 1 : 55;
figure(5);
loglog(x, fib_recursive, x, fib_looped, x, fib_memoized, x, fib_matrixed, 'LineWidth', 2);
lgd = legend(fib_recursive_name, fib_looped_name, fib_memoized_name, fib_matrixed_name);
lgd.Location = 'Best';
title('Fibonacci: Recursive vs. Looped vs. Cached vs. Matrixed');


figure(6);
plot(x, fib_recursive, x, fib_looped, x, fib_memoized, x, fib_matrixed, 'LineWidth', 2);
lgd = legend(fib_recursive_name, fib_looped_name, fib_memoized_name, fib_matrixed_name);
lgd.Location = 'NorthWest';
title('Fibonacci: Recursive vs. Looped vs. Cached vs. Matrixed');