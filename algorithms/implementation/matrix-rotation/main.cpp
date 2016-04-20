#include <iostream>
#include <vector>
#include <algorithm>

class matrix {
 private:
  int rows;

  int cols;

  std::vector<std::vector<int>> values;

  int layer(const int& x, const int& y) const {
    int dx = std::min(x, this->cols - x - 1);
    int dy = std::min(y, this->rows - y - 1);
    return std::min(dx, dy);
  }

  int get(int x, int y, int rotate) const {
    if (rotate <= 0) {
      return this->values[y][x];
    }

    int layer = this->layer(x, y);
    int dx = 0;
    int dy = 0;
    if (x == layer && y > layer) {
      dy = std::max(-rotate, layer - y);
    } else if (x == this->cols - 1 - layer && y < this->rows - 1 - layer) {
      dy = std::min(rotate, this->rows - 1 - layer - y);
    } else if (y == layer && x < this->cols - 1 - layer) {
      dx = std::min(rotate, this->cols - 1 - layer - x);
    } else {  // y == this->rows - 1 - layer && x > layer
      dx = std::max(-rotate, layer - x);
    }

    rotate -= std::abs(dx) + std::abs(dy);
    return this->get(x + dx, y + dy, rotate);
  }

 public:
  int rotate;

  matrix(int rows, int cols) : rows(rows), cols(cols),
    values(rows, std::vector<int>(cols)) {
  }

  int get(int x, int y) const {
    int layer = this->layer(x, y);
    int loop = 2 * (this->cols - layer * 2) + 2 * (this->rows - 2 - layer * 2);
    int rotate = this->rotate % loop;
    return this->get(x, y, rotate);
  }

  static matrix load(std::istream& in, int rows, int cols) { // NOLINT
    matrix m(rows, cols);
    for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
        in >> m.values[r][c];
      }
    }
    return m;
  }

  friend std::ostream& operator<< (std::ostream& out, const matrix& m);
};

std::ostream& operator<< (std::ostream& out, const matrix& m) {
  for (int y = 0; y < m.rows; ++y) {
    for (int x = 0; x < m.cols; ++x) {
      std::cout << m.get(x, y) << " ";
    }
    std::cout << std::endl;
  }
  return out;
}

int main() {
  int rows, cols, rotate;
  std::cin >> rows >> cols >> rotate;
  matrix m = matrix::load(std::cin, rows, cols);
  m.rotate = rotate;
  std::cout << m;
}
