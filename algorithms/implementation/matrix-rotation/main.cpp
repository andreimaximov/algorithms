#include <istream>
#include <iostream>
#include <algorithm>

typedef struct {
  int** matrix;
  int rows;
  int cols;
} matrix;

matrix load_matrix(std::istream &in, const int &rows, const int &cols) {
  matrix m;
  m.rows = rows;
  m.cols = cols;
  m.matrix = new int*[rows];
  for (int r = 0; r < rows; r++) {
    m.matrix[r] = new int[cols];
    for (int c = 0; c < cols; c++) {
      in >> m.matrix[r][c];
    }
  }

  return m;
}

int layer(const int &x, const int &y, const matrix &m) {
  int dx = std::min(x, m.cols - x - 1);
  int dy = std::min(y, m.rows - y - 1);
  return std::min(dx, dy);
}

int get_cell_helper(int &x, int &y, int &r, const matrix &m) {
  if (r <= 0) {
    return m.matrix[y][x];
  }

  int in = layer(x, y, m);

  int dx = 0;
  int dy = 0;
  if (x == in && y > in) {
    dy = std::max(-r, in - y);
  } else if (x == m.cols - 1 - in && y < m.rows - 1 - in) {
    dy = std::min(r, m.rows - 1 - in - y);
  } else if (y == in && x < m.cols - 1 - in) {
    dx = std::min(r, m.cols - 1 - in - x);
  } else { // y == m.rows - 1 - in && x > in
    dx = std::max(-r, in - x);
  }

  x += dx;
  y += dy;
  r -= abs(dx) + abs(dy);
  return get_cell_helper(x, y, r, m);
}

int get_cell(int x, int y, int r, const matrix &m) {
  int in = layer(x, y, m);
  int loop = 2 * (m.cols - in * 2) + 2 * (m.rows - 2 - in * 2);
  r = r % loop;
  return get_cell_helper(x, y, r, m);
}

void print(const matrix &m, int rotate) {
  for (int y = 0; y < m.rows; y++) {
    for (int x = 0; x < m.cols; x++) {
      std::cout << get_cell(x, y, rotate, m) << " ";
    }
    std::cout << std::endl;
  }
}

int main() {
  int rows, cols, rotate;
  std::cin >> rows >> cols >> rotate;

  matrix m = load_matrix(std::cin, rows, cols);
  print(m, rotate);
}
