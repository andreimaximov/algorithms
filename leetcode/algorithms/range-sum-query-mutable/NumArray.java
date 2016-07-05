import java.util.Arrays;

public class NumArray {
  private int[] nodes;

  private int leafs;

  public NumArray(int[] nums) {
    leafs = nextFullTreeLeafs(nums.length);
    nodes = new int[leafs * 2 - 1];
    Arrays.fill(nodes, 0);
    for (int i = 0; i < nums.length; i++) {
      nodes[leafs + i - 1] = nums[i];
    }
    count(0);
  }

  /**
   * Calculates the smallest power of 2 that is greater than or equal to n. This
   * is useful for computing the number of leafs in the next full tree.
   */
  private int nextFullTreeLeafs(int n) {
    int leafs = 1;
    while (leafs < n) {
      leafs *= 2;
    }
    return leafs;
  }

  /**
   * Computes the sum cache for the node at the specified index.
   */
  private int count(int index) {
    if (index >= leafs - 1) {
      // Use the value if this is a leaf node...
      return nodes[index];
    }
    // Compute sum of of children for internal nodes...
    nodes[index] = count(index * 2 + 1) + count(index * 2 + 2);
    return nodes[index];
  }

  /**
   * Returns the parent index of a node at the specified index.
   */
  private int parent(int index) {
    return (index - 1) / 2;
  }

  /**
   * Updates the value at index in the original array with the specified value.
   */
  public void update(int index, int value) {
    index = leafs + index - 1;
    int delta = value - nodes[index];
    nodes[index] = value;
    // Propagate delta up through parents...
    while (index > 0) {
      index = parent(index);
      nodes[index] += delta;
    }
  }

  /**
   * Calculates the sum of integers between the index lo and hi inclusive.
   *
   * @param   qlo the first index of the query range
   * @param   qhi the last index of the query range
   * @param   slo the first index of the segment represented by the node at
   *          index i
   * @param   shi the last index of the segment represented by the node at index
   *          i
   * @param   i the index of the node the has the sum for range slo ... shi
   */
  private int sumRange(int qlo, int qhi, int slo, int shi, int i) {
    if (qlo > shi || qhi < slo) {
      // If the query is not in the segment at node i
      return 0;
    } else if (qlo <= slo && qhi >= shi) {
      // If the query is fully contained in the segment at node i
      return nodes[i];
    }

    // Compute the left and right sections separately if part of the segment at
    // node i contains the query range...
    int mid = slo + (shi - slo) / 2;
    int left = sumRange(qlo, qhi, slo, mid, i * 2 + 1);
    int right = sumRange(qlo, qhi, mid + 1, shi, i * 2 + 2);
    return left + right;
  }

  /**
   * Calculates the sum of integers between the index lo and hi inclusive.
   */
  public int sumRange(int lo, int hi) {
    return sumRange(lo, hi, 0, leafs - 1, 0);
  }

  public static void main(String[] args) {
    int[] nums = new int[] {1, 2, 3, 4, 5, 6, 7, 8, 9};
    NumArray numArr = new NumArray(nums);

    System.out.println(String.format("[0:8] = %d", numArr.sumRange(0, 8)));
    System.out.println(String.format("[3:7] = %d", numArr.sumRange(3, 7)));

    numArr.update(8, 10);

    System.out.println(String.format("[0:8] = %d", numArr.sumRange(0, 8)));
    System.out.println(String.format("[3:7] = %d", numArr.sumRange(3, 7)));
  }
}
