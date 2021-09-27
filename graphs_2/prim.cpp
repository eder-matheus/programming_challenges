void prim(std::vector<std::vector<int_pair>> &graph,
          std::vector<int> &predecessor) {
  std::priority_queue<int_pair, std::vector<int_pair>, std::greater<int_pair>>
      heap;
  int added[graph.size()];
  int costs[graph.size()];

  memset(costs, std::numeric_limits<int>::max(), sizeof(costs));
  heap.push({0, 0});

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
}