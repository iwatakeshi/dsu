% (A) Brute Force vs. Projected O(N!)

brute_force_small_time = [
% N       Time
  4     1.049783
  5     1.121833
  6     1.072799
  7     1.086988
  8     1.095723
  9     1.076412
  10    1.053085
];

T10 = 1.053085;

brute_force_small_projected_time = [
% N       Time
  4     1.049783
  5     1.121833
  6     1.072799
  7     1.086988
  8     1.095723
  9     T10 / 10
  10    T10
  11    T10 * 11
  12    T12 * 11 * T10
];
% Small N Test:

% -------------------------------------------------------------------------------------------------------------------------------------------------
% N = 4
% Algorithm                                         Average Cost        Average Quality                                   Average Time        
% -------------------------------------------------------------------------------------------------------------------------------------------------
% Brute (Non-recursive)                             14.000000           1.000000                                          1.049783            
% Greedy (Nearest Neighbor)                         17.000000           1.000000                                          0.000013            
% Monte Carlo (k = 1...100)                         2122.000000         99.700000                                         0.004024            
% Kruskal's MST + Two Approximate                   33.000000           1.900000                                          0.000067            
% Prim's MST + Two Approximate                      20.000000           1.000000                                          0.000117            
% Kruskal's MST + A*                                17.000000           1.000000                                          0.004396            
% Prim's MST + A*                                   18.000000           1.000000                                          0.004052            


% N = 5
% Algorithm                                         Average Cost        Average Quality                                   Average Time        
% -------------------------------------------------------------------------------------------------------------------------------------------------
% Brute (Non-recursive)                             14.000000           1.000000                                          1.121833            
% Greedy (Nearest Neighbor)                         17.000000           1.000000                                          0.000013            
% Monte Carlo (k = 1...100)                         2493.000000         111.200000                                        0.004198            
% Kruskal's MST + Two Approximate                   38.000000           2.000000                                          0.000081            
% Prim's MST + Two Approximate                      21.000000           1.000000                                          0.000124            
% Kruskal's MST + A*                                17.000000           1.000000                                          0.005009            
% Prim's MST + A*                                   21.000000           1.100000                                          0.004056            


% N = 6
% Algorithm                                         Average Cost        Average Quality                                   Average Time        
% -------------------------------------------------------------------------------------------------------------------------------------------------
% Brute (Non-recursive)                             17.000000           1.000000                                          1.072799            
% Greedy (Nearest Neighbor)                         19.000000           1.000000                                          0.000013            
% Monte Carlo (k = 1...100)                         2723.000000         106.400000                                        0.004117            
% Kruskal's MST + Two Approximate                   47.000000           2.300000                                          0.000077            
% Prim's MST + Two Approximate                      26.000000           1.000000                                          0.000128            
% Kruskal's MST + A*                                19.000000           1.000000                                          0.004627            
% Prim's MST + A*                                   23.000000           1.000000                                          0.004046            


% N = 7
% Algorithm                                         Average Cost        Average Quality                                   Average Time        
% -------------------------------------------------------------------------------------------------------------------------------------------------
% Brute (Non-recursive)                             19.000000           1.000000                                          1.086988            
% Greedy (Nearest Neighbor)                         23.000000           1.000000                                          0.000017            
% Monte Carlo (k = 1...100)                         3335.000000         109.400000                                        0.004153            
% Kruskal's MST + Two Approximate                   54.000000           2.300000                                          0.000079            
% Prim's MST + Two Approximate                      33.000000           1.200000                                          0.000119            
% Kruskal's MST + A*                                23.000000           1.000000                                          0.004533            
% Prim's MST + A*                                   29.000000           1.100000                                          0.003989            


% N = 8
% Algorithm                                         Average Cost        Average Quality                                   Average Time        
% -------------------------------------------------------------------------------------------------------------------------------------------------
% Brute (Non-recursive)                             19.000000           1.000000                                          1.095723            
% Greedy (Nearest Neighbor)                         23.000000           1.000000                                          0.000013            
% Monte Carlo (k = 1...100)                         3524.000000         138.100000                                        0.004352            
% Kruskal's MST + Two Approximate                   57.000000           2.700000                                          0.000093            
% Prim's MST + Two Approximate                      32.000000           1.100000                                          0.000130            
% Kruskal's MST + A*                                23.000000           1.000000                                          0.004949            
% Prim's MST + A*                                   26.000000           1.000000                                          0.004210            


% N = 9
% Algorithm                                         Average Cost        Average Quality                                   Average Time        
% -------------------------------------------------------------------------------------------------------------------------------------------------
% Brute (Non-recursive)                             24.000000           1.000000                                          1.076412            
% Greedy (Nearest Neighbor)                         29.000000           1.000000                                          0.000014            
% Monte Carlo (k = 1...100)                         4126.000000         119.700000                                        0.004006            
% Kruskal's MST + Two Approximate                   68.000000           2.400000                                          0.000076            
% Prim's MST + Two Approximate                      41.000000           1.200000                                          0.000127            
% Kruskal's MST + A*                                29.000000           1.000000                                          0.004712            
% Prim's MST + A*                                   36.000000           1.000000                                          0.004201            


% N = 10
% Algorithm                                         Average Cost        Average Quality                                   Average Time        
% -------------------------------------------------------------------------------------------------------------------------------------------------
% Brute (Non-recursive)                             26.000000           1.000000                                          1.053085            
% Greedy (Nearest Neighbor)                         31.000000           1.000000                                          0.000013            
% Monte Carlo (k = 1...100)                         4697.000000         130.600000                                        0.004084            
% Kruskal's MST + Two Approximate                   74.000000           2.400000                                          0.000078            
% Prim's MST + Two Approximate                      44.000000           1.200000                                          0.000118            
% Kruskal's MST + A*                                31.000000           1.000000                                          0.004494            
% Prim's MST + A*                                   42.000000           1.100000                                          0.004012