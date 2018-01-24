#include <iostream>
#include <vector>

const int16_t DELTA_X[] = {-1, 0, 1, 1, 1, 0, -1, -1};
const int16_t DELTA_Y[] = {-1, -1, -1, 0, 1, 1, 1, 0};

typedef std::vector<std::vector<int>> matrix;

matrix load(int m, int n) {
  matrix mtx(m, std::vector<int>(n));
  for (int i = 0; i < m; ++i) {
    for (int k = 0; k < n; ++k) {
      std::cin >> mtx[i][k];
    }
  }
  return mtx;
}

int floodfill(matrix& mtx, int row, int col) { // NOLINT
  int size = 1;
  mtx[row][col] = 0;
  for (int i = 0; i < 8; ++i) {
    int16_t x = col + DELTA_X[i];
    int16_t y = row + DELTA_Y[i];
    // Check if out of bounds
    if (x < 0 || x >= mtx[y].size() || y < 0 || y >= mtx.size()) {
      continue;
    }
    // Out of region or already visited
    if (mtx[y][x] == 0) {
      continue;
    }
    size += floodfill(mtx, y, x);
  }
  return size;
}

int maxregion(matrix& mtx) { // NOLINT
  int largest = 0;
  for (int r = 0; r < mtx.size(); ++r) {
    for (int c = 0; c < mtx[r].size(); ++c) {
      // Skip visited cells
      if (mtx[r][c] == 0) {
        continue;
      }
      largest = std::max(largest, floodfill(mtx, r, c));
    }
  }
  return largest;
}

int main() {
  int m, n;
  std::cin >> m >> n;
  matrix mtx = load(m, n);
  std::cout << maxregion(mtx) << std::endl;;
  return 0;
}
