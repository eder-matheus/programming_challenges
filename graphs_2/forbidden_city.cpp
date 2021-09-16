// forbidden city - uri 2528

#include <iostream>
#include <limits>
#include <list>
#include <queue>
#include <vector>

typedef std::pair<int, int> int_pair;

void dijkstra(int source, std::vector<std::vector<int_pair>> &graph,
              std::vector<int> &predecessor, std::vector<int> &costs,
              int blocked) {
  std::priority_queue<int_pair, std::vector<int_pair>, std::greater<int_pair>>
      heap;
  std::vector<int> added(graph.size(), 0);

  heap.push({0, source});
  costs[source] = 0;
  costs[blocked] = -1;

  while (!heap.empty()) {
    int vertex = heap.top().second;
    heap.pop();
    added[vertex] = 1;

    for (int i = 0; i < graph[vertex].size(); i++) {
      int adj = graph[vertex][i].second;
      if (added[adj] == 0 &&
          (graph[vertex][i].first + costs[vertex]) < costs[adj]) {
        costs[adj] = graph[vertex][i].first + costs[vertex];
        heap.push({costs[adj], adj});
        predecessor[adj] = vertex;
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int num_cities, num_routes;
  int ctb, rdf, eu;

  while (std::cin >> num_cities >> num_routes) {
    std::vector<std::vector<int_pair>> graph(num_cities);
    std::vector<int> predecessor(num_cities);
    std::vector<int> costs(num_cities, std::numeric_limits<int>::max());

    for (int i = 0; i < num_routes; i++) {
      int city0, city1;
      std::cin >> city0 >> city1;
      city0--;
      city1--;
      graph[city0].push_back({1, city1});
      graph[city1].push_back({1, city0});
    }

    std::cin >> ctb >> rdf >> eu;
    ctb--;
    rdf--;
    eu--;

    dijkstra(ctb, graph, predecessor, costs, eu);
    int j;
    std::cout << costs[rdf];
    std::cout << "\n";
  }

  return 0;
}