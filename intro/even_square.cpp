// print the square of each one of the even values from 1 to N
#include <iostream>
#include <cmath>
 
int main() {
  int n;

  std::cin >> n;

  for (int i = 1; i <= n; i++) {
    if ((i % 2) == 0) {
      int square = pow(i, 2);
      std::cout << i << "^" << 2 << " = " << square << "\n";
    }
  }

  return 0;
}
