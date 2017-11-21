#ifndef TSP_H
#define TSP_H
#include "edge.hpp"
#include "graph.hpp"
#include "mst.hpp"
#include <chrono>
#include <random>
#include <stack>
#include <string>
#include <vector>

class TSP {
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

  static void
  print(std::tuple<int, std::vector<int>> solution) {
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