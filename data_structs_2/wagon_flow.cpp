// wagon flow - uri 2857

#include <iostream>
#include <vector>

const int ENTER = 1;
const int QUERY = 2;

void buildSegTree(std::vector<int> &wagon_tree, const std::vector<int> &wagons,
                  int node, int begin, int end) {
  if (begin == end) {
    wagon_tree[node] = wagons[end];
  } else {
    int middle = (begin + end) / 2;
    buildSegTree(wagon_tree, wagons, 2 * node, begin, middle);
    buildSegTree(wagon_tree, wagons, 2 * node + 1, middle + 1, end);
    wagon_tree[node] = wagon_tree[2 * node] + wagon_tree[2 * node + 1];
  }
}

void updateSegTree(std::vector<int> &wagon_tree, int position, int value,
                   int node, int begin, int end) {
  if (begin == end) {
    wagon_tree[node] += value;
  } else {
    int middle = (begin + end) / 2;
    if (position <= middle) {
      updateSegTree(wagon_tree, position, value, 2 * node, begin, middle);
    } else {
      updateSegTree(wagon_tree, position, value, 2 * node + 1, middle + 1, end);
    }
    wagon_tree[node] = wagon_tree[2 * node] + wagon_tree[2 * node + 1];
  }
}

int getSum(const std::vector<int> &wagon_tree, int first, int last, int node,
           int begin, int end) {
  if (first > last) {
    return 0;
  }

  if (begin == first && end == last) {
    return wagon_tree[node];
  }

  int middle = (begin + end) / 2;
  return getSum(wagon_tree, first, std::min(middle, last), 2 * node, begin,
                middle) +
         getSum(wagon_tree, std::max(first, middle + 1), last, 2 * node + 1,
                middle + 1, end);
}

int getPersonsCount(const std::vector<int> &wagon_tree, int first0, int last0,
                    int first1, int last1, int num_wagons) {
  int cnt = 0;

  if ((first0 <= last1) && (first1 <= last0)) {
    int first = std::min(first0, first1);
    int last = std::max(last0, last1);

    cnt = getSum(wagon_tree, first, last, 1, 0, num_wagons -1);
  } else {
    cnt += getSum(wagon_tree, first0, last0, 1, 0, num_wagons - 1);
    cnt += getSum(wagon_tree, first1, last1, 1, 0, num_wagons - 1);
  }

  return cnt;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int num_wagons, activities_cnt;
  std::cin >> num_wagons >> activities_cnt;

  std::vector<int> wagons(num_wagons, 0);
  std::vector<int> wagon_tree(4 * num_wagons);
  buildSegTree(wagon_tree, wagons, 1, 0, num_wagons - 1);
  for (int i = 0; i < activities_cnt; i++) {
    int act;
    std::cin >> act;
    if (act == ENTER) {
      int wagon, persons_cnt;
      std::cin >> wagon >> persons_cnt;
      wagon--;
      updateSegTree(wagon_tree, wagon, persons_cnt, 1, 0, num_wagons -1);
    } else {
      int first0, last0, first1, last1;
      std::cin >> first0 >> last0 >> first1 >> last1;
      first0--;
      last0--;
      first1--;
      last1--;
      int cnt = getPersonsCount(wagon_tree, first0, last0, first1, last1, num_wagons);
      std::cout << cnt << "\n";
    }
  }

  return 0;
}