// manyfile - uri 2545

#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <vector>

void inverted_dfs(int vertex, const std::vector<std::vector<int>> &graph,
                  std::vector<int> &expanded, std::list<int> &topology) {
  expanded[vertex] = 1;
  for (int i = 0; i < graph[vertex].size(); i++) {
    int adjacent = graph[vertex][i];
    if (expanded[adjacent] == 0) {
      inverted_dfs(adjacent, graph, expanded, topology);
    }
  }

  topology.push_back(vertex);
}

int getLongestPath(const std::vector<std::vector<int>> &graph) {
  int longest_path = -1;
  std::vector<int> expanded(graph.size(), 0);
  std::list<int> topology;
  for (int i = 0; i < graph.size(); i++) {
    if (expanded[i] == 0) {
      inverted_dfs(i, graph, expanded, topology);
    }

    std::vector<int> distance(graph.size(), std::numeric_limits<int>::min());
    distance[i] = 0;
    while (!topology.empty()) {
      int vertex = topology.back();
      topology.pop_back();

      if (distance[vertex] != std::numeric_limits<int>::min()) {
        for (int adj : graph[vertex]) {
          if (distance[adj] < distance[vertex] + 1) {
            distance[adj] = distance[vertex] + 1;
          }
        }
      }
    }

    if (distance[i] != 0) {
      longest_path = -1;
      break;
    }
    for (int j = 0; j < graph.size(); j++) {
      longest_path = std::max(longest_path, distance[j]);
    }
  }

  return longest_path;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  const int num_cores = 4096;

  int file_count;

  while (std::cin >> file_count) {
    std::vector<std::vector<int>> graph(file_count);

    for (int file = 0; file < file_count; file++) {
      int dependencies_count;
      std::cin >> dependencies_count;
      for (int i = 0; i < dependencies_count; i++) {
        int dependency;
        std::cin >> dependency;
        dependency--;
        graph[dependency].push_back(file);
      }
    }

    int longest_path = getLongestPath(graph);

    int total_time =
        (longest_path != -1)
            ? std::ceil((float)file_count / num_cores) + longest_path
            : -1;
    std::cout << total_time << "\n";
  }

  return 0;
}
