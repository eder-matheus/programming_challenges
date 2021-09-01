// allowance - uri 2546

#include <iostream>
#include <string>
#include <vector>

struct Allowance {
  int grandchild;
  int value;

  bool operator<(const Allowance &a) const { return value < a.value; }

  Allowance() {
    grandchild = -1;
    value = -1;
  }
};

void buildSegTree(std::vector<Allowance> &seg_tree,
                  const std::vector<Allowance> &vec, int node, int begin,
                  int end) {
  if (begin == end) {
    seg_tree[node] = vec[end];
  } else {
    int middle = (begin + end) / 2;
    buildSegTree(seg_tree, vec, 2 * node, begin, middle);
    buildSegTree(seg_tree, vec, 2 * node + 1, middle + 1, end);
    seg_tree[node] = std::max(seg_tree[2 * node], seg_tree[2 * node + 1]);
  }
}

Allowance getMax(std::vector<Allowance> &seg_tree, std::vector<int> &lazy,
                 int first, int last, int node, int begin, int end) {
  if (lazy[node] != 0) {
    seg_tree[node].value += lazy[node];
    if (begin != end) {
      lazy[2 * node] += lazy[node];
      lazy[2 * node + 1] += lazy[node];
    }
    lazy[node] = 0;
  }

  if ((end < first) || (begin > last)) {
    return Allowance();
  }

  if (begin >= first && end <= last) {
    return seg_tree[node];
  }

  int middle = (begin + end) / 2;
  return std::max(getMax(seg_tree, lazy, first, std::min(middle, last),
                         2 * node, begin, middle),
                  getMax(seg_tree, lazy, std::max(first, middle + 1), last,
                         2 * node + 1, middle + 1, end));
}

void rangeUpdateSegTree(std::vector<Allowance> &seg_tree,
                        std::vector<int> &lazy, int first, int last, int value,
                        int node, int begin, int end) {
  if (lazy[node] != 0) {
    seg_tree[node].value += lazy[node];

    if (begin != end) {
      lazy[2 * node] += lazy[node];
      lazy[2 * node + 1] += lazy[node];
    }

    lazy[node] = 0;
  }

  if ((end < first) || (begin > last)) {
    return;
  }

  if (begin >= first && end <= last) {
    seg_tree[node].value += value;
    if (begin != end) {
      lazy[2 * node] += value;
      lazy[2 * node + 1] += value;
    }
    return;
  }

  int middle = (begin + end) / 2;
  rangeUpdateSegTree(seg_tree, lazy, first, std::min(middle, last), value,
                     2 * node, begin, middle);
  rangeUpdateSegTree(seg_tree, lazy, std::max(first, middle + 1), last, value,
                     2 * node + 1, middle + 1, end);
  seg_tree[node] = std::max(seg_tree[2 * node], seg_tree[2 * node + 1]);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int allowances_count, operations_count;

  while (std::cin >> allowances_count >> operations_count) {
    std::vector<Allowance> seg_tree(4 * allowances_count);
    std::vector<int> lazy(4 * allowances_count, 0);
    std::vector<Allowance> allowances(allowances_count);
    for (int i = 0; i < allowances_count; i++) {
      allowances[i].grandchild = i;
      std::cin >> allowances[i].value;
    }

    buildSegTree(seg_tree, allowances, 1, 0, allowances_count - 1);

    for (int i = 0; i < operations_count; i++) {
      char op;
      std::cin >> op;
      if (op == 'A') {
        int first, last, value;
        std::cin >> first >> last >> value;
        first--;
        last--;
        rangeUpdateSegTree(seg_tree, lazy, first, last, value, 1, 0,
                           allowances_count - 1);
      } else {
        int first, last;
        std::cin >> first >> last;
        first--;
        last--;
        Allowance max =
            getMax(seg_tree, lazy, first, last, 1, 0, allowances_count - 1);
        std::cout << max.grandchild + 1 << "\n";
      }
    }
  }

  return 0;
}
