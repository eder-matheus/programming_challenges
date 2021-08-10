// knight scape
#include <iostream>
#include <cmath>

const int dimension = 8;
const int num_pieces = 9;

void findKnightMoviments(bool board[dimension][dimension], int row, int col) {
  for (int r = -2; r <= 2; r++) {
    for (int c = -2; c <= 2; c++) {
      if ((abs(r) == 2 && abs(c) == 1) ||
          (abs(r) == 1 && abs(c) == 2)) {
        if (((row + r) >= 0 && (row + r) < dimension) &&
            ((col + c) >= 0 && (col + c) < dimension)) {
          board[row + r][col + c] = true;
        }
      }
    }
  }
}

void findPawnsAttacks(bool board[dimension][dimension], int row, int col) {
  int attack_row = row - 1;
  int attack_col1 = col + 1;
  int attack_col2 = col - 1;

  if (attack_row < dimension) {
    if (attack_col1 < dimension) {
      board[attack_row][attack_col1] = false;
    }
    if (attack_col2 > 0) {
      board[attack_row][attack_col2] = false;
    }
  }
}

int main() {
  bool board[dimension][dimension] = {false};

  int row = -1;
  int col;
  char column;

  int cnt = 0;
  int test = 1;
  while (row != 0) {
    scanf("%d%c", &row, &column);
    col = (int)column - 96;

    // first row of input --> knight position
    if (cnt == 0) {
      findKnightMoviments(board, row-1, col-1);
    } else { // other rows --> pawns position
      findPawnsAttacks(board, row-1, col-1);
    }

    cnt++;

    if (cnt == num_pieces) {
      int valid_moviments = 0;
      for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
          if (board[i][j]) {
            valid_moviments++;
            board[i][j] = false;
          }
        }
      }

      std::cout << "Caso de Teste #" << test << ": " << valid_moviments << " movimento(s).\n";
      cnt = 0;
      test++;
    }
  }

  return 0;
}
