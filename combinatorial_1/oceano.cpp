// oceano profundo - uri 1398

#include <iostream>
#include <cmath>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  std::string binary_num;

  while (std::cin >> binary_num) {
    std::string bin_2;
    while (binary_num.back() != '#') {
      std::cin >> bin_2;
      binary_num += bin_2;
      bin_2.clear();
    }

    int number = 0;
    int pos = binary_num.size() - 2;
    for (int i = 0; i < binary_num.size(); i++) {
      if (binary_num[i] == '1') {
        number = 2 * number + 1;
        number %= 131071;
      }
      pos--;
    }

    if (number % 131071 == 0) {
      std::cout << "YES\n";
    } else {
      std::cout << "NO\n";
    }
  }

  return 0;
}
