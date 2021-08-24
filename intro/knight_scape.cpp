// knight scape
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

const int dimension = 8;
const int num_pieces = 9;

void findKnightMoviments(int row, int col, std::vector<std::pair<int, int> >& movements) {
  for (int r = -2; r <= 2; r++) {
    for (int c = -2; c <= 2; c++) {
      if ((abs(r) == 2 && abs(c) == 1) ||
          (abs(r) == 1 && abs(c) == 2)) {
        if (((row + r) >= 0 && (row + r) < dimension) &&
            ((col + c) >= 0 && (col + c) < dimension)) {
          movements.push_back(std::pair<int, int>(row+r, col+c));
        }
      }
    }
  }
}

void findPawnsAttacks(int row, int col, std::vector<std::pair<int, int> >& movements) {
  int attack_row = row - 1;
  int attack_col1 = col + 1;
  int attack_col2 = col - 1;

  if (attack_row < dimension) {
    if (attack_col1 < dimension) {
      movements.erase(
        std::remove(
            movements.begin(),
            movements.end(),
            std::pair<int, int>(attack_row, attack_col1)),
            movements.end());
    }
    if (attack_col2 >= 0) {
      movements.erase(
        std::remove(
            movements.begin(),
            movements.end(),
            std::pair<int, int>(attack_row, attack_col2)),
            movements.end());
    }
  }
}

int main() {
  int row = -1;
  char column;
  std::vector<std::pair<int, int> > movements;

  int cnt = 0;
  int test = 1;
  while (row != 0) {
    scanf("%d%c", &row, &column);
    int col = (int)column - 96;

    // first row of input --> knight position
    if (cnt == 0) {
      findKnightMoviments(row-1, col-1, movements);
    } else { // other rows --> pawns position
      findPawnsAttacks(row-1, col-1, movements);
    }

    cnt++;

    if (cnt == num_pieces) {
      std::cout << "Caso de Teste #" << test << ": " << movements.size() << " movimento(s).\n";
      cnt = 0;
      test++;
      movements.clear();
    }
  }

  return 0;
}
