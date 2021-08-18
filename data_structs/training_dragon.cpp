// training dragon

#include <iostream>
#include <algorithm>
#include <vector>

struct Dragon {
  long long int days_to_train_;
  long long int fee_per_day_;
  int curr_day_;

  Dragon(long long int days_to_train, long long int fee_per_day, int curr_day) {
    days_to_train_ = days_to_train;
    fee_per_day_ = fee_per_day;
    curr_day_ = curr_day;
  }

  float computeCost() const {
    return (float)days_to_train_/fee_per_day_;
  }
};

struct greater1 {
  bool operator()(const Dragon& d0, const Dragon& d1) const {
    return d0.computeCost() > d1.computeCost();
  }
};

int main() {
  int days_to_train, cost_to_train;
  long long int total_fee = 0;
  int total_days = 0;
  int training_days = 0;
  std::vector<Dragon> dragons;
  std::make_heap(dragons.begin(), dragons.end(), greater1());

  while (std::cin >> days_to_train >> cost_to_train) {
    dragons.push_back(Dragon(days_to_train, cost_to_train, total_days));
    std::push_heap(dragons.begin(), dragons.end(), greater1());

    // when previous training end, choose another dragon
    if (training_days == 0) {
      // get dragon with largest cost
      Dragon dragon = dragons.front();
      std::pop_heap(dragons.begin(), dragons.end(), greater1());
      dragons.pop_back();
      // get the fee for the dragon multiplying the number of days it is waiting for training
      total_fee += (total_days-dragon.curr_day_)*dragon.fee_per_day_;
      training_days = dragon.days_to_train_;
    }
    training_days--;
    total_days++;
  }

  // same logic from above for the remaining dragons, after all were sent
  while (!dragons.empty()) {
    if (training_days == 0) {
      Dragon dragon = dragons.front();
      std::pop_heap(dragons.begin(), dragons.end(), greater1());
      dragons.pop_back();
      total_fee += (total_days-dragon.curr_day_)*dragon.fee_per_day_;
      training_days = dragon.days_to_train_;
    }
    training_days--;
    total_days++;
  }

  std::cout << total_fee << "\n";

  return 0;
}
