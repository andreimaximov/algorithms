public class Solution {
  /**
   * Finds the median of two integers.
   */
  public double findMedian(int a, int b) {
    return (a + b) / 2.0;
  }

  /**
   * Finds the median of three integers.
   */
  public double findMedian(int a, int b, int c) {
    int min = Math.min(a, Math.min(b, c));
    int max = Math.max(a, Math.max(b, c));
    return a + b + c - min - max;
  }

  /**
   * Finds the median of four integers.
   */
  public double findMedian(int a, int b, int c, int d) {
    int min = Math.min(a, Math.min(b, Math.min(c, d)));
    int max = Math.max(a, Math.max(b, Math.max(c, d)));
    return (a + b + c  + d - min - max) / 2.0;
  }

  /**
   * Finds the median of a single sorted sub-array a[lo] ... a[hi] or -1 if the
   * sub-array is empty.
   */
  public double findMedianSortedArray(int[] a, int lo, int hi) {
    if (hi - lo < 0) {
      return -1;
    }
    int length = hi - lo + 1;
    int left = lo + (length - 1) / 2;
    int right = lo + length / 2;
    return (a[left] + a[right]) / 2.0;
  }

  /**
   * Finds the median of two sorted sub-arrays a[alo] ... a[ahi] and b[blo] ...
   * b[bhi]. Sub-array a is expected to be shorter or equal to the length of
   * sub-array b.
   */
  public double findMedianSortedArrays(int[] a, int alo, int ahi,
                                       int[] b, int blo, int bhi) {
    // Calculate the sub-array lengths...
    int alength = ahi - alo + 1;
    int blength = bhi - blo + 1;

    // Return the median of b if a is empty...
    if (alength == 0) {
      return findMedianSortedArray(b, blo, bhi);
    }

    if (alength == 1) {
      if (blength == 1) {
        // Find the median of the only two elements...
        return findMedian(a[alo], b[blo]);
      } else if (blength % 2 != 0) {
        // Find the median of the middle 3 elements in b + the only element in
        // a...
        return findMedian(a[alo],
                          b[blo + blength / 2 - 1],
                          b[blo + blength / 2],
                          b[blo + blength / 2 + 1]);
      } else {
        // Find the median of the middle 2 elements in b + the only element
        // in a...
        return findMedian(a[alo],
                          b[blo + blength / 2 - 1],
                          b[blo + blength / 2]);
      }
    } else if (alength == 2) {
      if (blength == 2) {
        // Find the median of the only 4 elements...
        return findMedian(a[alo], a[alo + 1], b[blo], b[blo + 1]);
      } else if (blength % 2 != 0) {
        // Find the median of the middle 3 elements in b + the 2 elements in
        // a...
        return findMedian(b[blo + blength / 2],
                          Math.max(a[alo], b[blo + blength / 2 - 1]),
                          Math.min(a[alo + 1], b[blo + blength / 2 + 1]));
      } else {
        // Find the median of the middle 4 elements in b + the 2 elements in
        // a...
        return findMedian(b[blo + blength / 2],
                          b[blo + blength / 2 - 1],
                          Math.max(a[alo], b[blo + blength / 2 - 2]),
                          Math.min(a[alo + 1], b[blo + blength / 2 + 1]));
      }
    }

    // Find and compare the middle elements in each sub-array...
    int ai = (alength - 1) / 2;
    int bi = (blength - 1) / 2;

    // Trim sub-arrays from start/end by ai depending on middle comparison...
    if (a[alo + ai] < b[blo + bi]) {
      // Continue search in a[alo + ai ...] and b[... bhi - ai]
      alo = alo + ai;
      bhi = bhi - ai;
    } else {
      // Continue search in a[... ahi - ai] and b[blo + ai ...]
      ahi = ahi - ai;
      blo = blo + ai;
    }

    return findMedianSortedArrays(a, alo, ahi, b, blo, bhi);
  }

  /**
   * Finds the median of two sorted arrays a and b.
   */
  public double findMedianSortedArrays(int[] a, int[] b) {
    if (a.length > b.length) {
      return findMedianSortedArrays(b, 0, b.length - 1, a, 0, a.length - 1);
    }
    return findMedianSortedArrays(a, 0, a.length - 1, b, 0, b.length - 1);
  }

  public static void main(String[] args) {
    int[] a = {1, 3, 5, 7, 9};
    int[] b = {2, 4, 6, 8};

    Solution sol = new Solution();
    double m = sol.findMedianSortedArrays(a, b);

    if (Math.abs(m - 5) > 0.001) {
      System.err.println(String.format("Expected median 5 but got %f.", m));
    } else {
      System.out.println(String.format("Got median of %f", m));
    }
  }
}
