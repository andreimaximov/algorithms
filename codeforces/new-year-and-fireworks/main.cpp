#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::istream_iterator;
using std::copy;

//
// Max 30 recursion levels -> at most 5 * 30 = 150 offset in +/- x or +/- y
// direction from starting point.
//
#define GRID_N 301

//
// The maximum firework explosion recursions.
//
#define LEVELS 30

//
// Defines the directions of travel for fireworks.
//
const int DIRS[8][2] = {{0, 1}, {1, 1}, {1, 0}, {1, -1},
                        {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

//
// Defines an N-dimensional matrix of type T.
//
template<size_t N, typename T>
struct Matrix {
  typedef vector<typename Matrix<N - 1, T>::type> type;
};

template<typename T>
struct Matrix<0, T> {
  typedef T type;
};

//
// Runs DFS starting at (x, y) in DIRS[d] direction. Returns the number of
// previously unexplored locations.
//
int dfs(size_t i,
         const vector<int>& T,
         size_t x,
         size_t y,
         size_t d,
         Matrix<4, bool>::type& dp,  // NOLINT
         Matrix<2, bool>::type& visit) {  // NOLINT
  // Do not continue if (1) this is beyond the last level of recursion or (2)
  // we have fired a firework with the same recursion layer and direction at
  // this point.
  if (i == T.size() || dp[x][y][i][d]) {
    return 0;
  }

  // Mark this points as visited.
  int count = !visit[x][y] ? 1 : 0;
  dp[x][y][i][d] = true;
  visit[x][y] = true;
  int t = T[i];

  // Traverse all points along firework path and count unvisited locations.
  while (t > 1) {
    x += DIRS[d][0];
    y += DIRS[d][1];
    count += !visit[x][y] ? 1 : 0;
    visit[x][y] = true;
    t--;
  }

  // Create and fire off two children at 45 degree angles. Ensure we count any
  // unvisited points they encounter as well.
  size_t l = (d - 1) % 8;
  count += dfs(i + 1, T, x + DIRS[l][0], y + DIRS[l][1], l, dp, visit);
  size_t r = (d + 1) % 8;
  count += dfs(i + 1, T, x + DIRS[r][0], y + DIRS[r][1], r, dp, visit);
  return count;
}

int main() {
  int n;
  cin >> n;
  vector<int> T(n);
  copy(istream_iterator<int>(cin),
       istream_iterator<int>(),
       T.begin());

  Matrix<4, bool>::type dp(
      GRID_N, Matrix<3, bool>::type(
      GRID_N, Matrix<2, bool>::type(
      LEVELS, Matrix<1, bool>::type(8))));

  Matrix<2, bool>::type visit(GRID_N, Matrix<1, bool>::type(GRID_N));

  // Start at the center of the grid so we don't segfault from going out of
  // bounds.
  cout << dfs(0, T, GRID_N / 2, GRID_N / 2, 0, dp, visit) << endl;
  return 0;
}
