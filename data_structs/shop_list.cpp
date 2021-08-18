// shop list

#include <iostream>
#include <iomanip>
#include <map>
 
int main() {
  int num_cases;
  std::cin >> num_cases;

  for (int i = 0; i < num_cases; i++) {
    std::map<std::string, float> product_to_price_map;
    int num_prods;

    std::cin >> num_prods;
    for (int j = 0; j < num_prods; j++) {
      std::string prod_name;
      float price;
      std::cin >> prod_name >> price;
      product_to_price_map[prod_name] = price;
    }

    int buy_items;
    float total_cost = 0;

    std::cin >> buy_items;
    for (int j = 0; j < buy_items; j++) {
      std::string prod_name;
      float qtt;
      std::cin >> prod_name >> qtt;
      total_cost += qtt * product_to_price_map[prod_name];
    }

    std::cout << std::fixed << std::setprecision(2) << "R$ " << total_cost << "\n";
  }

  return 0;
}
