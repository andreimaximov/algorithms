public class Solution {
  //
  // Computes the edit distance (Levenshtein Distance) between two strings.
  //
  // If either a or b is length 0, we must add/remove max(length(a), length(b))
  // characters to have identical strings.
  //
  // If the last characters of a and b are the same, we recurse on a[:-1], b[:-1].
  //
  // Otherwise we return 1 + min of the these three candidate operations:
  //
  // 1. Adding the last character of a -> a[:-1], b
  // 2. Removing the last character of a -> a, b[:-1]
  // 3. Swapping the last character of a -> a[:-1], b[:-1]
  //
  public int minDistance(String a, String b) {
    int[][] matrix = new int[a.length() + 1][b.length() + 1];

    for (int i = 0; i < matrix.length; i++) {
      for (int j = 0; j < matrix[i].length; j++) {
        if (i == 0) {
          matrix[i][j] = j;
        } else if (j == 0) {
          matrix[i][j] = i;
        } else if (a.charAt(i - 1) == b.charAt(j - 1)) {
          matrix[i][j] = matrix[i - 1][j - 1];
        } else {
          matrix[i][j] = 1 + min(matrix[i - 1][j],
                                 matrix[i][j - 1],
                                 matrix[i - 1][j - 1]);
        }
      }
    }

    return matrix[a.length()][b.length()];
  }

  //
  // Returns the smallest of three integers.
  //
  public int min(int a, int b, int c) {
    return Math.min(a, Math.min(b, c));
  }

  public static void main(String[] args) {
    System.out.println("Please run this solution on LeetCode.");
    System.out.println("https://leetcode.com/problems/edit-distance/");
  }
}
