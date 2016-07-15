import java.util.Arrays;
import java.util.Random;

public class Solution {
  public void setZeroes(int[][] matrix) {
    // Check for invalid matrix...
    if (matrix == null || matrix.length == 0) {
      return;
    }

    // Track columns and rows with 0's...
    boolean[] rows = new boolean[matrix.length];
    boolean[] cols = new boolean[matrix[0].length];

    // Find columns and rows with 0's...
    for (int r = 0; r < matrix.length; r++) {
      for (int c = 0; c < matrix[r].length; c++) {
        if (matrix[r][c] == 0) {
          rows[r] = true;
          cols[c] = true;
        }
      }
    }

    // Fill columns with 0's...
    for (int r = 0; r < rows.length; r++) {
     if (rows[r]) {
       Arrays.fill(matrix[r], 0);
     }
    }

    // Fill rows with 0's...
    for (int c = 0; c < cols.length; c++) {
     if (cols[c]) {
       for (int r = 0; r < rows.length; r++) {
         matrix[r][c] = 0;
       }
     }
    }
  }

  public static void main(String[] args) {
    System.out.println("Please run this solution on LeetCode.");
    System.out.println("https://leetcode.com/problems/set-matrix-zeroes/");
  }
}
