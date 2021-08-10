// detect perfect numbers
#include <iostream>
 
int main() {
  int n, x;

  std::cin >> n;

  for (int i = 0; i < n; i++) {
    std::cin >> x;
    int sum = 0;
    for (int d = 1; d <= x/2; d++) {
      if ((x % d) == 0) {
        sum += d;
      }
    }

    if (sum == x) {
      std::cout << x << " eh perfeito\n";
    } else {
      std::cout << x << " nao eh perfeito\n";
    }
  }

  return 0;
}
