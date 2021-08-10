// sum of consecutive odd numbers III
#include <iostream>

int main() {
  int n, x, y;

  std::cin >> n;

  for (int i = 0; i < n; i++) {
    std::cin >> x >> y;
    int sum = 0;
    if (x % 2 == 0) {
      x++;
    }

    for (int j = 0; j < y; j++) {
      sum += x + 2*j;
    }

    std::cout << sum << "\n";
  }

  return 0;
}
