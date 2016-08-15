import java.util.Arrays;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Solution {
  private static final int[] TEST_ARRAY = {1, 1, 1, 2, 2, 2, 3, 4};

  private static final List<Integer> TEST_MAJORITY_ELEMENT =
      Arrays.asList(1, 2);

  //
  // Returns elements that occur more than n / 3 times. There can be at most 2
  // such elements. If 2 elements occur more than n / 3 times, that means there
  // are less than n / 3 spots left for all other elements. Thus there can only
  // be one or two majority elements.
  //
  // Uses modified Moore's Voting algorithm.
  //
  public List<Integer> majorityElement(int[] nums) {
    if (nums == null) {
      return Collections.emptyList();
    }

    // Initialize majority elements to 0. Duplicates are handled naturally at
    // the end.
    int intA = 0;
    int intB = 0;
    int countA = 0;
    int countB = 0;

    // Finds elements that might occur more than n / 3 times.
    for (int i : nums) {
      if (i == intA) {
        countA++;
      } else if (i == intB) {
        countB++;
      } else if (countA == 0) {
        intA = i;
        countA = 1;
      } else if (countB == 0) {
        intB = i;
        countB = 1;
      } else {
        countA--;
        countB--;
      }
    }

    List<Integer> result = new ArrayList<>();

    // Check that the two candidate elements actually occur more than n / 3
    // times.
    countA = 0;
    countB = 0;
    for (int i : nums) {
      if (i == intA) {
        countA++;
      } else if (i == intB) {
        countB++;
      }
    }

    if (countA > nums.length / 3) {
      result.add(intA);
    }
    if (countB > nums.length / 3) {
      result.add(intB);
    }

    return result;
  }

  public static void main(String[] args) {
    Solution solution = new Solution();
    assert TEST_MAJORITY_ELEMENT.equals(solution.majorityElement(TEST_ARRAY));

    System.out.println("Tests pass!");
    System.out.println("Please run this solution on LeetCode.");
    System.out.println("https://leetcode.com/problems/majority-element-ii/");
  }
}