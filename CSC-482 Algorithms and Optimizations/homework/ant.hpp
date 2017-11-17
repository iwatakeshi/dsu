#ifndef ANT_H
#define ANT_H
#include "graph.hpp"
#include <cmath>
#include <random>
#include <vector>

std::random_device __ant_rseed;
std::mt19937 __ant_rgen(__ant_rseed());
std::uniform_int_distribution<double> __double_ant_dist(0, 100);

class AntParameters {
      public:
  // Amount of trail
  double c = 1.0;
  // Trail preference
  double alpha = 1;
  // Greedy preference
  double beta = 5;
  // Trail evaporation coefficient
  double evaporation = 1;
  // New trail deposit (pheremone) coefficient
  double Q = 500;
  // Number of ants used (multiplier * towns)
  double ant_multiplier = 0.8;
  // Probability of random town selection
  double pr = 0.01;
};

class Ant {
  private:
  Graph graph;
  std::vector<int> _tour;
  std::vector<bool> _visited;
  std::vector <std::vector<int>>& _trails;

  public:
  Ant() {
    _trails.reserve(1);
    _trails[0].reserve(1);
  }
  Ant(Graph graph, std::vector<std::vector<int>> & trails) {
    this->graph = graph;
    _tour.resize(graph.size());
    _visited.resize(graph.size());
    _trails = trails;
  }

  std::vector<std::vector<int>> trails() {
    return _trails;
  }

  std::vector<int> tour() {
    return _tour;
  }

  int tour(int index) {
    return _tour.at(index);
  }

  int distance() {
    int weight = graph.edgeWeight(_tour[graph.size() - 1], _tour[0]);
    for (int i = 0; i < graph.size() - 1; i++) {
      weight += graph.edgeWeight(_tour[i], _tour[i + 1]);
    }
    return weight;
  }

  void visit(int town, int position) {
    _tour[position + 1] = town;
    _visited[town] = true;
  }

  bool visited(int town) {
    return _visited[town];
  }

  void forget() {
    for (int i = 0; i < graph.size(); i++) {
      _visited[i] = false;
    }
  }

  Graph& map() {
    return graph;
  }

  static std::vector<double>& move_probability(Ant ant, std::vector<double>& probs, AntParameters param, int position) {
    int i = ant.tour(position);
    auto alpha = param.alpha;
    auto beta = param.beta;
    auto trails = ant.trails();
    auto graph = ant.map();

    double denominator = 0.0;
    for (int j = 0; j < graph.size(); j++) {
      if (!ant.visited(j)) {
        denominator += std::pow(trails[i][j], alpha) * std::pow(1.0 / graph.at(i, j), beta);
      } else {
        probs[j] = 0.0;
      }
    }

    for (int j = 0; j < graph.size(); j++) {
      if (!ant.visited(j)) {
        double numerator = std::pow(trails[i][j], alpha) * std::pow(1.0 / graph.at(i, j), beta);
        probs[j] = numerator / denominator;
      }
    }
    return probs;
  }

  static int select_next_town(Ant ant, AntParameters param, int position) {
    auto pr = param.pr;
    auto size = ant.map().size();
    std::uniform_int_distribution<int> __int_ant_dist(0, std::abs(size - position));
    if (__double_ant_dist(__ant_rgen) < pr) {
      int n = -1, town = __int_ant_dist(__ant_rgen);
      for (int i = 0; i < size; i++) {
        if (!ant.visited(i)) {
          n++;
        }
        if (n == town) {
          return town;
        }
      }
    }

    auto probs = Ant::move_probability(ant);

    double r = __double_ant_dist(__ant_rgen);
    double t = 0;
    for (int i = 0; i < size; i++) {
      t += probs[i];
      if (t >= r) {
        return i;
      }
    }

    throw "An error occurred when selecting a town";
  }
};

#endif