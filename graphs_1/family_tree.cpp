// family tree - uri 2854

#include <iostream>
#include <map>
#include <vector>
#include <list>

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

int getFirstNotExpanded(const std::vector<int> &expanded) {
  for (int i = 0; i < expanded.size(); i++) {
    if (expanded[i] == 0) {
      return i;
    }
  }

  return -1;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int persons_count, relations_count;

  while (std::cin >> persons_count >> relations_count) {
    std::vector<std::vector<int> > family_tree(persons_count);
    std::vector<int> expanded(persons_count, 0);

    std::map<std::string, int> person_to_idx_map;
    int person_idx = 0;

    for (int i = 0; i < relations_count; i++) {
      std::string person0, relation, person1;
      std::cin >> person0 >> relation >> person1;
      if (person_to_idx_map.find(person0) == person_to_idx_map.end()) {
        person_to_idx_map[person0] = person_idx;
        person_idx++;
      }
      if (person_to_idx_map.find(person1) == person_to_idx_map.end()) {
        person_to_idx_map[person1] = person_idx;
        person_idx++;
      }

      int p0 = person_to_idx_map[person0];
      int p1 = person_to_idx_map[person1];
      family_tree[p0].push_back(p1);
      family_tree[p1].push_back(p0);
    }

    int idx = getFirstNotExpanded(expanded);
    int family_count = 0;
    while (idx != -1) {
      dfs(idx, family_tree, expanded);
      family_count++;
      idx = getFirstNotExpanded(expanded);
    }

    std::cout << family_count << "\n";
  }

  return 0;
}