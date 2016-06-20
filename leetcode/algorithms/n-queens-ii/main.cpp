#include <iostream>
#include <vector>
#include <string>

//
// Tracks row, diagonal, and anit-diagonal Queen attacking state of a board.
//
class State {
 private:
  std::vector<bool> cols;

  std::vector<bool> diags;

  std::vector<bool> anti;

  size_t n;

 public:
  explicit State(size_t n) : cols(n), diags(2 * n), anti(2 * n), n(n) {
  }

  //
  // Returns a bool indicating if the (row, col) cell is under attack by an
  // existing Queen.
  //
  inline bool isValid(size_t row, size_t col) {
    if (cols[col] || diags[row - col + n] || anti[row + col]) {
      return false;
    }
    return true;
  }

  //
  // Updates the state by setting a Queen at the specified (row, col) cell.
  //
  inline void set(size_t row, size_t col) {
    cols[col] = true;
    diags[row - col + n] = true;
    anti[row + col] = true;
  }

  //
  // Updates the state by erasing a Queen from the specified (row, col) cell.
  //
  inline void erase(size_t row, size_t col) {
    cols[col] = false;
    diags[row - col + n] = false;
    anti[row + col] = false;
  }
};

class Solution {
 public:
  int totalNQueens(State& state, size_t row, size_t n) { // NOLINT
    if (row == n) {
      return 1;  // End of algorithm...
    }
    uint64_t total = 0;
    for (size_t col = 0; col < n; col++) {
      // Check if we can place a Queen here...
      if (!state.isValid(row, col)) {
        continue;
      }
      // Place Queen here and DFS...
      state.set(row, col);
      total += totalNQueens(state, row + 1, n);
      state.erase(row, col);
    }
    return total;
  }

  int totalNQueens(int n) {
    State state(n);
    return totalNQueens(state, 0, n);
  }
};

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Please specify N." << std::endl;
    return 1;
  }
  int N = std::stoi(argv[1]);
  Solution solution;
  std::cout << solution.totalNQueens(N) << std::endl;
  return 0;
}
