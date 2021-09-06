// noel's delivery - uri 2476

#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <vector>

int distanceBFS(int origin, int objective,
                const std::vector<std::vector<int>> &graph,
                const std::vector<std::string> &requested_gifts) {
  std::list<int> expand;
  std::vector<int> expanded(graph.size(), 0);
  std::vector<int> distance(graph.size());

  expand.push_back(origin);
  expanded[origin] = 1;
  distance[origin] = 1;

  std::set<std::string> given_gifts;
  while (!expand.empty()) {
    int vertex = expand.front();
    expand.pop_front();

    given_gifts.insert(requested_gifts[vertex]);
    for (int i = 0; i < graph[vertex].size(); i++) {
      int adjacent = graph[vertex][i];
      if (expanded[adjacent] == 0) {
        expand.push_back(adjacent);
        expanded[adjacent] = 1;
        distance[adjacent] = distance[vertex] + 1;
        if (!given_gifts.insert(requested_gifts[adjacent]).second) {
          distance[adjacent]--;
        }
        if (adjacent == objective)
          return distance[objective];
      }
    }
  }

  return distance[objective];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int houses_cnt, questions_cnt;
  std::cin >> houses_cnt >> questions_cnt;

  std::vector<std::vector<int>> graph(houses_cnt);
  std::vector<int> expanded(houses_cnt, 0);
  std::vector<std::string> requested_gifts(houses_cnt);

  for (int i = 0; i < houses_cnt; i++) {
    std::cin >> requested_gifts[i];
  }

  for (int i = 0; i < houses_cnt - 1; i++) {
    int h0, h1;
    std::cin >> h0 >> h1;
    h0--;
    h1--;
    graph[h0].push_back(h1);
    graph[h1].push_back(h0);
  }

  for (int i = 0; i < questions_cnt; i++) {
    int h0, h1;
    std::cin >> h0 >> h1;
    h0--;
    h1--;

    std::cout << distanceBFS(h0, h1, graph, requested_gifts) << "\n";
  }

  return 0;
}
