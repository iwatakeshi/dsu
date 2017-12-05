#ifndef TSP_H
#define TSP_H
#include "edge.hpp"
#include "graph.hpp"
#include "mst.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <random>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

typedef typename std::tuple<int, std::vector<int>, std::string> tsp_t;

class TSP {
  private:
  template <typename func>
  auto min_by(std::vector<int>& vector, func f) {
    std::vector<std::tuple<int, int>> temp;
    std::transform(vector.begin(), vector.end(), std::back_inserter(temp), [&](int x) {
      return std::make_tuple(x, f(x));
    });
    std::sort(temp.begin(), temp.end(), [](std::tuple<int, int> a, std::tuple<int, int> b) {
      return std::get<1>(a) < std::get<1>(b);
    });
    return std::get<0>(temp[0]);
  }

  void dynamic_trace_back_(std::vector<std::vector<int>>& dp, std::vector<int>& tour, int i, int end) {
    if (i == 0) {
      tour.push_back(0);
    } else {
      std::vector<int> k(graph.size());
      std::iota(k.begin(), k.end(), 0);
      auto val = min_by(k, [&](int x) -> int {
        auto v = dp[i][x] + graph.get_edge(end, x).weight();
        return v < 0 ? std::numeric_limits<int>::max() : v;
      });
      tour.push_back(val);
      dynamic_trace_back_(dp, tour, i ^ (1 << val), val);
    }
  }
  auto dynamic_trace_back(std::vector<std::vector<int>>& dp) {
    std::vector<int> tour;
    tour.push_back(0);
    auto mask = ((1 << graph.size()) - 1) ^ 1;
    dynamic_trace_back_(dp, tour, mask, 0);
    int distance = 0;
    for (int i = 0; i < tour.size() - 1; i++) {
      auto edge = graph.get_edge(tour[i], tour[i + 1]);
      distance += edge.weight();
    }
    return std::make_tuple(distance, tour);
  }
  auto dynamic_recursive_(std::vector<std::vector<int>>& dp, int mask, int pos) {
    auto dist = graph.cost_matrix();

    if (mask == (1 << graph.size()) - 1) {
      return dist[pos][0];
    }

    if (dp[mask][pos] != std::numeric_limits<int>::max()) {
      return dp[mask][pos];
    }
    
    // Set the best distance as max
    int best_distance = std::numeric_limits<int>::max();
    int first_step;
    // Travel to unvisited vertices
    for (int w = 0; w < graph.size(); w++) {
      // Make sure we haven't visisted vertex w
      if ((mask & (1 << w)) == 0) {
        int distance = dist[pos][w] + dynamic_recursive_(dp, mask | (1 << w), w);
        if (distance < best_distance) {
          best_distance = distance;
        }
      }
    }
    return dp[mask][pos] = best_distance;
  }

  public:
  Graph graph;
  MST mst;
  TSP(int n, unsigned int low, unsigned int high) {
    graph = Graph(n, low, high);
    mst = MST(graph);
  }
  TSP(Graph* graph, MST* mst) {
    this->graph = *graph;
    this->mst = *mst;
  };

  TSP(std::vector<std::vector<int>> matrix) {
    graph = Graph(matrix);
    mst = MST(graph);
  }

  // A non-recursive approach in order to avoid confusion
  auto brute() {
    int best_distance = std::numeric_limits<int>::max();
    std::vector<int> best_tour;
    std::vector<int> tour(graph.size());
    // Create tour
    for (int i = 0; i < tour.size(); i++) {
      tour[i] = i;
    }

    // Permutate the tours
    while (std::next_permutation(tour.begin(), tour.end())) {
      // Calculate the distance
      int current_distance = graph.get_edge(tour[0], tour[tour.size() - 1]).weight();
      for (int i = 1; i < tour.size(); i++) {
        current_distance += graph.get_edge(tour[i - 1], tour[i]).weight();
      }

      // Set the best distance and tour when found
      if (current_distance < best_distance) {
        best_distance = current_distance;
        best_tour = tour;
      }
    }

    // Add the final destination
    best_tour.push_back(0);
    return make_tuple(best_distance, best_tour, "Brute (Non-recursive)");
  }
  // Credits: http://www.cs.ucf.edu/~dmarino/progcontests/modules/dptsp/DP-TSP-Notes.pdf
  auto dynamic() {
    int n = graph.size();
    std::vector<std::vector<int>> dp(1 << n, std::vector<int>(n, std::numeric_limits<int>::max()));
    dp[0][0] = 0;
    auto bit_check = [&](int a, int b) {
      return (b & (1 << a)) > 0;
    };

    // Generate the minimum sub-distance
    // Credits: https://jet1black.wordpress.com/2015/07/22/bitmask-dp-on-tsp/
    for (int i = 0; i < (1 << n); i++) {
      for (int j = 0; j < n; j++) {
        if (bit_check(j, i)) {
          auto mask = i ^ (1 << j);
          std::vector<int> k(n);
          std::iota(k.begin(), k.end(), 0);

          std::transform(k.begin(), k.end(), k.begin(), [&](int x) -> int {
            auto val = dp[mask][x] + graph.get_edge(x, j).weight();
            return val < 0 ? std::numeric_limits<int>::max() : val;
          });
          std::sort(k.begin(), k.end());

          dp[i][j] = k[0];
        }
      }
    }
    auto result = dynamic_trace_back(dp);

    return std::make_tuple(std::get<0>(result), std::get<1>(result), "Dynamic Programming (Non-recursive)");
  }

  auto dynamic_recursive() {
    std::vector<std::vector<int>> dp(1 << graph.size(), std::vector<int>(graph.size(), std::numeric_limits<int>::max()));
    dp[0][0] = 0;
    dynamic_recursive_(dp, 1, 0);
    auto result = dynamic_trace_back(dp);

    return std::make_tuple(std::get<0>(result), std::get<1>(result), "Dynamic Programming");
  }

  auto greedy() {
    int distance = 0;
    std::vector<int> visited;
    std::vector<int> tour;
    // Current vertex will start from vertex 0
    int current = 0;
    int next;
    tour.push_back(current);

    int size = graph.size();
    visited.push_back(current);

    // Repeat until all vertices are visisted
    while (visited.size() != size) {
      int min = std::numeric_limits<int>::max();
      // Find nearest vertex (loop over vertices)
      for (int j = 0; j < size; j++) {
        // Vertex not visited
        if (std::find(visited.begin(), visited.end(), j) == visited.end()) {
          auto weight = graph.get_edge(current, j).weight();
          if (min > weight) {
            min = weight;
            next = j;
          }
        }
      }

      // Get the weight of the current -> next
      distance += graph.get_edge(current, next).weight();
      current = next;
      // The vertex has been visited
      visited.push_back(current);
      // Add the vertex to the tour
      tour.push_back(current);
    }
    // Get the final distance from last -> home
    distance += graph.get_edge(tour[tour.size() - 1], 0).weight();
    // Add 0 as the final destination
    tour.push_back(0);
    return make_tuple(distance, tour, "Greedy (Nearest Neighbor)");
  }

  auto montecarlo(const int k) {
    int best_distance = std::numeric_limits<int>::max();
    std::vector<int> tour = graph.vertices(), best_tour;
    // Remove 0 from the tour
    auto it = std::find_if(tour.begin(), tour.end(), [](int number) {
      return number == 0;
    });
    if (it != tour.end()) tour.erase(it);
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    /* Shuffles the vector */
    auto uniform_shuffle = [](std::vector<int>& tour, unsigned seed) {
      shuffle(tour.begin(), tour.end(), std::default_random_engine(seed));
    };
    /* Calculate the tour's distance (total weight)*/
    auto tour_distance = [](Graph& graph, std::vector<int>& tour) {
      int distance = 0;
      // Calculate the weight from 0 --> next
      distance += graph.get_edge(0, tour[0]).weight();
      // Calculate the weight from next --> 0 (final edge)
      distance += graph.get_edge(tour[tour.size() - 1], 0).weight();

      // Calculate the weight
      for (int i = 0; i < tour.size() - 1; i++) {
        distance += graph.get_edge(tour[i], tour[i + 1]).weight();
      }
      return distance;
    };

    int counter = 0;
    while (counter < k) {
      // Shuffle the tour
      uniform_shuffle(tour, seed);
      // Get the distance
      int distance = tour_distance(graph, tour);
      if (distance < best_distance) {
        best_distance = distance;
        best_tour = tour;
      }
      counter++;
    }
    // Insert the source
    best_tour.insert(best_tour.begin(), 0);
    // Insert the destination
    best_tour.push_back(0);
    return make_tuple(best_distance, best_tour, ("Monte Carlo (k = " + std::to_string(k) + ")"));
  }

  auto two_approximate(MSTGenerator generator) {
    mst.generate(generator);
    auto mgraph = mst.to_graph();
    // tree.print();
    std::vector<int> tour;
    std::vector<int> best_tour;
    // Initially mark all verices as not visited
    std::vector<bool> visited(mgraph.vertices().size(), false);
    // Create a stack for distance calculation
    std::stack<int> tour_stack;
    // Create a stack for DFS
    std::stack<int> stack;

    int current = 0;
    // Push the current source node.
    stack.push(current);

    while (!stack.empty()) {
      current = stack.top();
      stack.pop();

      if (!visited[current]) {
        tour.push_back(current);
        visited[current] = true;
      }

      auto adj = mgraph.adjacent_vertex(current);
      for (auto i = adj.begin(); i != adj.end(); ++i)
        if (!visited[*i]) {
          stack.push(*i);
        }
    }

    tour.push_back(0);
    for (auto i : tour) {
      tour_stack.push(i);
    }

    best_tour = tour;

    std::reverse(tour.begin(), tour.end());
    int distance = 0;

    // Calculate the distance
    auto v = tour_stack.top();
    tour_stack.pop();
    while (!tour_stack.empty()) {
      auto w = tour_stack.top();
      tour_stack.pop();
      auto e = graph.get_edge(v, w);
      distance += e.weight();
      v = w;
    }
    return std::make_tuple(distance, best_tour, "Two-Approximate");
  }

  auto a_star(MSTGenerator generator) {
    auto compare = [](std::tuple<int, int> lhs, std::tuple<int, int> rhs) {
      return std::get<1>(lhs) < std::get<1>(rhs);
    };

    // The set of vertices already evaluated
    std::set<std::tuple<int, int>, decltype(compare)> open_set(compare);
    // The set of currently discovered vertices that are not evaluated yet.
    // Initially, only the start node is known.
    std::set<int> closed_set;

    // The starting point
    auto start = std::make_tuple(0, 0);
    auto has = [](std::set<int>& set, int v) {
      return set.find(v) != set.end() && set.size() > 0;
    };

    auto vertex = [](std::tuple<int, int> v) {
      return std::get<0>(v);
    };

    auto pop = [](std::set<std::tuple<int, int>, decltype(compare)>& set) {
      auto it = set.begin();
      set.erase(it);
      return std::get<0>(*it);
    };

    auto size = graph.size();
    auto visited = new int[size]();

    // Start has been visited
    closed_set.insert(vertex(start));
    int current = vertex(start);
    auto n_visited = 1;
    visited[current] = n_visited++;

    while (closed_set.size() != size) {
      for (int w = 0; w < size; w++) {
        if (w != current && graph.contains(current, w)) {
          if (!has(closed_set, w)) {
            // Generate a subgraph for the minimum spanning tree
            auto g = Graph::make_subgraph(graph, closed_set);
            MST t(g);
            t.generate(generator);
            int h = t.distance();
            open_set.insert(std::make_tuple(w, h + graph.cost_matrix()[current][w]));
          }
        }
      }
      current = pop(open_set);
      closed_set.insert(current);
      visited[current] = n_visited++;
    }

    std::vector<int> total_path(graph.size());
    for (int i = 1; i <= closed_set.size(); i++) {
      for (int j = 0; j < closed_set.size(); j++) {
        if (visited[j] == i) {
          total_path[i - 1] = j;
        }
      }
    }
    int distance = 0;
    for (int i = 0; i < total_path.size() - 1; i++) {
      distance += graph.cost_matrix()[total_path[i]][total_path[i + 1]];
    }
    distance += graph.get_edge(total_path[total_path.size() - 1], 0).weight();
    total_path.push_back(0);
    return make_tuple(distance, total_path, "A*");
  }

  static void print(std::tuple<int, std::vector<int>> solution) {
    auto distance = std::get<0>(solution);
    auto tour = std::get<1>(solution);
    char letters[26] = {
      'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
      'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
    };
    printf("Tour: ");
    for (int i = 0; i < tour.size(); i++) {
      printf("%c ", letters[tour[i]]);
      if (i != tour.size() - 1) {
        printf("--> ");
      }
    }
    printf("\n");
    printf("Distance: %d\n", distance);
  }

  static void print(std::tuple<int, std::vector<int>, std::string> solution) {
    auto distance = std::get<0>(solution);
    auto tour = std::get<1>(solution);
    auto name = std::get<2>(solution);
    char letters[26] = {
      'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
      'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
    };

    printf("%s:\n", name.c_str());

    printf("Tour: ");
    for (int i = 0; i < tour.size(); i++) {
      printf("%c ", letters[tour[i]]);
      if (i != tour.size() - 1) {
        printf("--> ");
      }
    }
    printf("\n");
    printf("Distance: %d\n", distance);
  }
  static std::string tour_to_string(std::vector<int> tour) {
    std::string letters[26] = {
      "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
      "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"
    };
    std::string str = "";
    for (int i = 0; i < tour.size(); i++) {
      str += letters[tour[i]] + " ";
      if (i != tour.size() - 1) {
        str += "--> ";
      }
    }
    return str;
  }
};

#endif