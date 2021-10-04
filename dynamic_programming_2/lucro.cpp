// lucro - uri 1310

#include <iostream>
#include <vector>

int computeProfit(const std::vector<int> &profit_per_day, int first, int days) {
  int profit = 0;
  for (int i = first; i < days; i++) {
    profit += profit_per_day[i];
  }

  return profit;
}

int maxProfit(const std::vector<int> &profit_per_day, int first, int days,
              std::vector<std::vector<int>> &table) {
  if (table[first][days] >= 0) {
    return table[first][days];
  }
  if (days == 0) {
    table[first][days] = 0;
    return 0;
  }

  int max_profit = computeProfit(profit_per_day, first, days);

  if (first < days) {
    max_profit =
        std::max(max_profit, maxProfit(profit_per_day, first + 1, days, table));
    max_profit =
        std::max(max_profit, maxProfit(profit_per_day, first, days - 1, table));
  }

  table[first][days] = max_profit;

  return max_profit;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int num_days, cost_per_day;
  while (std::cin >> num_days >> cost_per_day) {
    std::vector<int> profit_per_day(num_days);
    std::vector<std::vector<int>> table(num_days + 1);
    for (std::vector<int> &v : table) {
      v.resize(num_days + 1, -1);
    }
    for (int i = 0; i < num_days; i++) {
      std::cin >> profit_per_day[i];
      profit_per_day[i] -= cost_per_day;
    }
    std::cout << maxProfit(profit_per_day, 0, num_days, table) << "\n";
  }

  return 0;
}
