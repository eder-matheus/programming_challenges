// strings - uri 2842

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

int solution(const std::string &w1, const std::string &w2, int s1, int s2,
             std::vector<std::vector<int>> &table) {
  if (table[s1][s2] >= 0) {
    return table[s1][s2];
  }
  if (s1 == 0 || s2 == 0) {
    table[s1][s2] = std::max(s1, s2);
    return std::max(s1, s2);
  }

  int str_size = 0;

  if (w1[s1-1] == w2[s2-1]) {
    str_size = 1 + solution(w1, w2, s1 - 1, s2 - 1, table);
  } else {
    str_size = 1 + std::min(solution(w1, w2, s1, s2 - 1, table),
                            solution(w1, w2, s1 - 1, s2, table));
  }

  table[s1][s2] = str_size;

  return str_size;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  std::string w1, w2;
  std::cin >> w1 >> w2;

  std::vector<std::vector<int>> table(w1.size() + 1);
  for (std::vector<int> &v : table) {
    v.resize(w2.size() + 1, -1);
  }

  std::cout << solution(w1, w2, w1.size(), w2.size(), table) << "\n";

  return 0;
}
