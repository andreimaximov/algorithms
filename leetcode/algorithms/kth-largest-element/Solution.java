import java.util.Arrays;
import java.util.Random;

public class Solution {
  private Random random = new Random();

  //
  // Finds the Kth largest int in the nums array.
  //
  public int findKthLargest(int[] nums, int k) {
    k = nums.length - k;
    return findKthIndex(nums, k);
  }

  //
  // Finds the Kth + 1 smallest int in the nums array.
  //
  public int findKthIndex(int[] nums, int k) {
    int lo = 0;
    int hi = nums.length - 1;
    int pivot = 0;
    do {
      pivot = between(lo, hi);
      pivot = partition(nums, lo, hi, pivot);
      if (pivot < k) {
        lo = pivot + 1;
      } else if (pivot > k) {
        hi = pivot - 1;
      }
    } while (pivot != k);
    return nums[k];
  }

  //
  // Returns a random integer between lo and hi inclusive.
  //
  private int between(int lo, int hi) {
    return random.nextInt(hi - lo + 1) + lo;
  }

  //
  // Partitions the nums array around a pivot index and returns the index of
  // the pivot index.
  //
  private int partition(int[] nums, int lo, int hi, int pivot) {
    // Store the element to pivot around...
    int around = nums[pivot];
    // Move the pivot element to the end...
    int end = hi;
    swap(nums, pivot, end);
    // Partition...
    while (lo < hi) {
      while (lo < hi && nums[lo] < around) lo++;
      while (lo < hi && nums[hi] >= around) hi--;
      if (lo >= hi) break;
      swap(nums, lo, hi);
    }
    // Move pivot element back to center...
    swap(nums, lo, end);
    return lo;
  }

  //
  // Swaps nums[x] and nums[y].
  //
  private void swap(int[] nums, int x, int y) {
    int tmp = nums[x];
    nums[x] = nums[y];
    nums[y] = tmp;
  }

  //
  // Generates an array of n random integers.
  //
  public static int[] generate(int n) {
    int[] nums = new int[n];
    Random random = new Random();
    for (int i = 0; i < n; i++) {
      nums[i] = random.nextInt();
    }
    return nums;
  }

  public static void main(String[] args) {
    if (args.length < 1) {
      System.err.println("Please specify K.");
      System.exit(1);
    }
    int k = Integer.parseInt(args[0]);
    Solution solution = new Solution();
    int[] nums = generate(10);

    // Generate an array of random integers...
    System.out.println("Generated numbers...");
    System.out.println(Arrays.toString(nums));

    // Calculate...
    int kth = solution.findKthLargest(nums, k);

    // Check solution..
    Arrays.sort(nums);
    if (kth != nums[nums.length - k]) {
      System.err.println(String.format("%d is incorrect!", kth));
      System.exit(2);
    }

    System.out.println(solution.findKthLargest(nums, k));
  }
}
