// criancas em uma grade - uri 1341

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

std::string parsePath(const std::vector<std::vector<char>> &grid, int x0,
                      int y0, const std::string &path) {
  int x = x0;
  int y = y0;
  std::string final_path;
  final_path.push_back(grid[x][y]);
  for (const char &c : path) {
    switch (c) {
    case 'N':
      x--;
      break;
    case 'E':
      y++;
      break;
    case 'W':
      y--;
      break;
    case 'S':
      x++;
      break;
    default:
      std::cout << "Invalid direction\n";
      exit(1);
    }
    final_path.push_back(grid[x][y]);
  }

  return final_path;
}

int solution(const std::string &w1, const std::string &w2, int s1, int s2,
             std::vector<std::vector<int>> &table) {
  if (table[s1][s2] >= 0) {
    return table[s1][s2];
  }
  if (s1 == 0 || s2 == 0) {
    table[s1][s2] = 0;
    return table[s1][s2];
  }

  int major = 0;
  if (w1[s1 - 1] == w2[s2 - 1]) {
    major = 1 + solution(w1, w2, s1 - 1, s2 - 1, table);
  } else {
    major = std::max(solution(w1, w2, s1 - 1, s2, table),
                     solution(w1, w2, s1, s2 - 1, table));
  }

  table[s1][s2] = major;
  return major;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int num_cases;
  std::cin >> num_cases;

  for (int i = 1; i <= num_cases; i++) {
    int rows, cols;
    std::cin >> rows >> cols;
    std::vector<std::vector<char>> grid(rows);
    for (int i = 0; i < rows; i++) {
      grid[i].resize(cols);
    }

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        std::cin >> grid[i][j];
      }
    }

    int steps1, x1, y1;
    std::string path1;
    std::cin >> steps1 >> x1 >> y1;
    x1--;
    y1--;
    if (steps1 > 0)
      std::cin >> path1;
    std::string w1 = parsePath(grid, x1, y1, path1);

    int steps2, x2, y2;
    std::string path2;
    std::cin >> steps2 >> x2 >> y2;
    x2--;
    y2--;
    if (steps2 > 0)
      std::cin >> path2;
    std::string w2 = parsePath(grid, x2, y2, path2);

    std::vector<std::vector<int>> table(w1.size() + 1);
    for (std::vector<int> &v : table) {
      v.resize(w2.size() + 1, -1);
    }

    int subseq_size = solution(w1, w2, w1.size(), w2.size(), table);

    std::cout << "Case " << i << ": " << w1.size() - subseq_size << " "
              << w2.size() - subseq_size << "\n";
  }

  return 0;
}
