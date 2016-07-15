public class Solution {
  //
  // Rotates the matrix 90 degrees clockwise.
  //
  // The idea is that for an NxN matrix, if we wish to rotate point (x, y) 90
  // degrees clockwise, we need to move 4 the following 4 points around the
  // matrix.
  //
  // (x, y), (n - 1 - y, r), (n - 1 - x, n - 1 - y), (y, n - 1 - r)
  //
  // We apply this rotation for all points by going through (row ... n - 1 - row)
  // points in the first n / 2 rows.
  //
  //
  public void rotate(int[][] matrix) {
    if (matrix == null || matrix.length < 2) {
      return;
    }
    int n = matrix.length;
    for (int layer = 0; layer < n / 2; layer++) {
      // Important to avoid last point in each layer! That's because the last
      // point on this side of the top side of the square is really the first
      // point on the right side where the first point on the top will be moved
      // to.
      for (int col = layer; col < n - layer - 1; col++) {
        int here = matrix[layer][col];
        matrix[layer][col] = matrix[n - 1 - col][layer];
        matrix[n - 1 - col][layer] = matrix[n - 1 - layer][n - 1 - col];
        matrix[n - 1 - layer][n - 1 - col] = matrix[col][n - 1 - layer];
        matrix[col][n - 1 - layer] = here;
      }
    }
  }

  public static void main(String[] args) {
    System.out.println("Please run this solution on LeetCode.");
    System.out.println("https://leetcode.com/problems/rotate-image/");
  }
}
