// a mesa quadrada de ines venezuela - uri 2069

#include <iostream>
#include <cmath>

#define MAX 100000

unsigned long long fatoracao(unsigned long long n1, unsigned long long n2) {
  unsigned long long f = 1;
  unsigned long long n = std::max(n1, n2);
  for (int i = 2; i * i <= n; i++) {
    int e1 = 0;
    if (n1 % i == 0) {
      while (n1 % i == 0) {
        e1++;
        n1 /= i;
      }
    }

    int e2 = 0;
    if (n2 % i == 0) {
      while (n2 % i == 0) {
        e2++;
        n2 /= i;
      }
    }

    f *= pow(i, (std::min(e1, e2) + (std::min(e1, e2) % 2)) / 2);
  }

  return f;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  unsigned i;
  unsigned long long a, b;
  unsigned long long fatores;

  std::cin >> a >> b;

  unsigned long long f = fatoracao(a, b);

  if (a == b)
    f *= a;

  std::cout << f << "\n";

  return 0;
}
