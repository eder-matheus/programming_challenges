// vogons! - uri 1834

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

struct Point {
  double x;
  double y;
};

struct Planet {
  Point position;
  int population;
};

double distance(const Point& p0, const Point& p1) {
  double dx = p1.x - p0.x;
  double dy = p1.y - p0.y;
  return sqrt(dx * dx + dy * dy);
}

int determinant(const Point& p0, const Point& p1, const Point& p2) {
  return (p0.x - p2.x) * (p1.y - p2.y) - (p1.x - p2.x) * (p0.y - p2.y);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  Point p0, p1;
  std::cin >> p0.x >> p0.y >> p1.x >> p1.y;

  int num_planets;
  std::cin >> num_planets;

  std::vector<Planet> planets(num_planets);

  for (int i = 0; i < num_planets; i++) {
    std::cin >> planets[i].position.x >> planets[i].position.y >>
        planets[i].population;
  }

  int west = 0, w_pop = 0;
  int east = 0, e_pop = 0;
  int casualties = 0;

  for (const Planet& p : planets) {
    int d = determinant(p0, p1, p.position);
    if (d < 0) {
      east++;
      e_pop += p.population;
    } else if (d > 0) {
      west++;
      w_pop += p.population;
    } else {
      casualties++;
    }
  }

  std::cout << "Relatorio Vogon #35987-2\n";
  std::cout << std::fixed << std::setprecision(2) << "Distancia entre referencias: " << distance(p0, p1) << " anos-luz\n";
  std::cout << "Setor Oeste:\n";
  std::cout << "- " << west << " planeta(s)\n";
  std::cout << "- " << w_pop << " bilhao(oes) de habitante(s)\n";
  std::cout << "Setor Leste:\n";
  std::cout << "- " << east << " planeta(s)\n";
  std::cout << "- " << e_pop << " bilhao(oes) de habitante(s)\n";
  std::cout << "Casualidades: " << casualties << " planeta(s)\n";

  return 0;
}
