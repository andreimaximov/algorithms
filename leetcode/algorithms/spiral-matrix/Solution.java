import java.util.Arrays;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;

public class Solution {
  private static final int[][] TEST_MATRIX = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
  };

  private static final List<Integer> TEST_SPIRAL =
      Arrays.asList(1, 2, 3, 6, 9, 8, 7, 4, 5);

  //
  // Traverses the m x n matrix and returns the spriral order of elements
  // starting at (0, 0) and conntinuing in a clockwise direction.
  //
  public List<Integer> spiralOrder(int[][] matrix) {
    if (matrix.length == 0) {
      return Collections.emptyList();
    }

    int m = matrix.length;
    int n = matrix[0].length;

    // Initialize traversal boundaries.
    int left = 0;
    int right = n - 1;
    int top = 0;
    int bottom = m - 1;

    List<Integer> spiral = new ArrayList<>(n * m);

    while (left <= right && top <= bottom) {
      // Go right.
      iterate(matrix, left, top, 1, 0, right + 1, top, spiral);

      // Go down. Skip top right element.
      iterate(matrix, right, top + 1, 0, 1, right, bottom + 1, spiral);

      // Go left if more than 1 row left. Skip bottom right element.
      if (bottom > top) {
        iterate(matrix, right - 1, bottom, -1, 0, left - 1, bottom, spiral);
      }

      // Go up if more than 1 column. Skip bottom left element and stop before
      // top. (This is why we also check for more than 1 row to avoid index out
      // of bounds exception in iteration)
      if (left < right && bottom > top) {
        iterate(matrix, left, bottom - 1, 0, -1, left, top, spiral);
      }

      // Update boundaries.
      left++;
      right--;
      top++;
      bottom--;
    }

    return spiral;
  }

  //
  // Traverses matrix starting at (x, y) until (ex, ey) using the specified
  // dx and dy and adds all encountered elements to the collection.
  //
  private void iterate(int[][] matrix, int x, int y, int dx, int dy,
                       int ex, int ey, Collection<Integer> collection) {
    while (x != ex || y != ey) {
      collection.add(matrix[y][x]);
      x += dx;
      y += dy;
    }
  }

  public static void main(String[] args) {
    Solution solution = new Solution();
    assert TEST_SPIRAL.equals(solution.spiralOrder(TEST_MATRIX));

    System.out.println("Tests pass!");
    System.out.println("Please run this solution on LeetCode.");
    System.out.println("https://leetcode.com/problems/spiral-matrix/");
  }
}