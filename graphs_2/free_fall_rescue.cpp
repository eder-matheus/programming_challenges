// free fall rescue - uri 1552

#include <cmath>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>
#include <iomanip>

typedef std::pair<double, int> node;

void prim(std::vector<std::vector<node>> &graph,
          std::vector<int> &predecessor) {
  std::priority_queue<node, std::vector<node>, std::greater<node>>
      heap;
  std::vector<int> added(graph.size(), 0);
  std::vector<double> costs(graph.size(), std::numeric_limits<int>::max());

  heap.push({0, 0});
  costs[0] = 0;

  while (!heap.empty()) {
    int vertex = heap.top().second;
    heap.pop();
    added[vertex] = 1;

    for (int i = 0; i < graph[vertex].size(); i++) {
      int adj = graph[vertex][i].second;
      if (added[adj] == 0 && graph[vertex][i].first < costs[adj]) {
        costs[adj] = graph[vertex][i].first;
        heap.push({costs[adj], adj});
        predecessor[adj] = vertex;
      }
    }
  }

  double cost = 0;
  for (int i = 0; i < graph.size(); i++) {
    cost += costs[i];
  }
  std::cout << std::fixed << std::setprecision(2) << cost/100 << "\n";
}

double distance(node p0, node p1) {
  int x0 = p0.first;
  int y0 = p0.second;
  int x1 = p1.first;
  int y1 = p1.second;
  return sqrt(
      (double)((abs(x1 - x0) * abs(x1 - x0) + abs(y1 - y0) * abs(y1 - y0))));
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int cases;
  std::cin >> cases;

  for (int i = 0; i < cases; i++) {
    int num_persons;
    std::cin >> num_persons;

    std::vector<std::vector<node>> graph(num_persons);
    std::vector<int> predecessor(num_persons);
    std::vector<node> persons(num_persons);

    for (int j = 0; j < num_persons; j++) {
      int x, y;
      std::cin >> x >> y;
      persons[j] = {x, y};
    }

    for (int j = 0; j < num_persons; j++) {
      for (int k = 0; k < num_persons; k++) {
        if (j != k) {
          graph[j].push_back({distance(persons[j], persons[k]), k});
          graph[k].push_back({distance(persons[j], persons[k]), j});
        } else {
          graph[j].push_back({0, k});
          graph[k].push_back({0, j});
        }
      }
    }

    prim(graph, predecessor);
  }

  return 0;
}
