// compute shortest path length
#include <iostream>
#include <sstream>
#include <iterator>
#include <map>
#include <cmath>
#include <vector>

int main() {
  int row = 0;
  int col = 0;
  int p0, p1, p2, p3;
  int cnt = 0;
  std::pair<int, int> my_pos;
  std::pair<int, int> mon_pos;

  std::string line;
  while (std::getline(std::cin, line)) {
    std::istringstream stream(line);
    std::vector<int> integers = std::vector<int> (std::istream_iterator<int>(stream),
                                                  std::istream_iterator<int>());

    if (integers.size() == 2 && cnt >= row) {
      row = integers[0];
      col = integers[1];
      cnt = 0;
    } else if (integers.size() == col) {
      int grid[row][col];
      
      for (int c = 0; c < col; c++){
        grid[cnt][c] = integers[c];
        if (integers[c] == 1) {
          my_pos.first = cnt;
          my_pos.second = c;
        } else if (integers[c] == 2) {
          mon_pos.first = cnt;
          mon_pos.second = c;
        }
      }

      cnt++;
      if (cnt == row) {
        int distance = abs(my_pos.first - mon_pos.first) +
                       abs(my_pos.second - mon_pos.second);
        std::cout << distance << "\n";
      }
    }
  }

  return 0;
}
