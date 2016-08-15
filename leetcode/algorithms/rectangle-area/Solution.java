public class Solution {
  //
  // Computes the union area of two rectangles.
  //
  public int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
    int areaX = (D - B) * (C - A);
    int areaY = (H - F) * (G - E);
    int total = areaX + areaY;
    int overlap = computeOverlap(A, B, C, D, E, F, G, H);
    return total - overlap;
  }

  //
  // Computes the intersection are of two rectangles.
  //
  public int computeOverlap(int A, int B, int C, int D, int E, int F, int G, int H) {
    // Check if there is no horizontal overlap.
    if (A > G || C < E) {
      return 0;
    }

    // Check if there is no vertical overlap.
    if (B > H || D < F) {
      return 0;
    }

    // Get width and height of square X. (Chosen arbitrarily)
    int width = G - E;
    int height = H - F;

    // Find the width and height of the overlap by subtracting the distance
    // between the edges of rectangle X and edges of rectangle Y for edges of Y
    // that are inside rectangle X.
    width -= (Math.max(0, A - E) + Math.max(0, G - C));
    height -= (Math.max(0, H - D) + Math.max(0, B - F));

    return width * height;
  }

  public static void main(String[] args) {
    System.out.println("Please run this solution on LeetCode.");
    System.out.println("https://leetcode.com/problems/rectangle-area/");
  }
}