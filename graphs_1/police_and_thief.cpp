// police and thief - uri 1905

#include <iostream>
#include <list>
#include <map>
#include <vector>

void dfs(int vertex, const std::vector<std::vector<int> > &graph,
         std::vector<int> &expanded) {
  expanded[vertex] = 1;
  for (int i = 0; i < graph[vertex].size(); i++) {
    int adjacent = graph[vertex][i];
    if (expanded[adjacent] == 0) {
      dfs(adjacent, graph, expanded);
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int num_cases;

  std::cin >> num_cases;

  for (int i = 0; i < num_cases; i++) {
    std::vector<std::vector<int> > grid(5);
    std::vector<std::vector<int> > graph(25);
    std::vector<int> expanded(25, 0);

    for (int row = 0; row < 5; row++) {
      grid[row].resize(5);
      for (int col = 0; col < 5; col++) {
        std::cin >> grid[row][col];
      }
    }

    for (int row = 0; row < 5; row++) {
      for (int col = 0; col < 5; col++) {
        if (col < 4) { // until the last element in the row, check the neighbor
                       // at right
          if (grid[row][col] == 0 && grid[row][col + 1] == 0) {
            graph[5 * row + col].push_back(5 * row + (col + 1));
            graph[5 * row + (col + 1)].push_back(5 * row + col);
          }
        }

        if (row < 4) { // until the last element in the col, check the neighbor
                       // at bottom
          if (grid[row][col] == 0 && grid[row + 1][col] == 0) {
            graph[5 * row + col].push_back(5 * (row + 1) + col);
            graph[5 * (row + 1) + col].push_back(5 * row + col);
          }
        }
      }
    }

    dfs(0, graph, expanded);

    if (expanded[24] != 0) {
      std::cout << "COPS\n";
    } else {
      std::cout << "ROBBERS\n";
    }
  }

  return 0;
}