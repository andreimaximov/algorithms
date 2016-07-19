public class Solution {
  //
  // Converts a sorted array to a balanced BST.
  //
  public TreeNode sortedArrayToBST(int[] array) {
    return sortedArrayToBST(array, 0, array.length - 1);
  }

  //
  // Converts sorted array array[lo] ... array[hi] to a balanced BST.
  //
  public TreeNode sortedArrayToBST(int[] array, int lo, int hi) {
    if (lo == hi) {
      return new TreeNode(array[lo]);
    } else if (hi < lo) {
      return null;
    }

    int mid = lo + (hi - lo) / 2;
    TreeNode node = new TreeNode(array[mid]);
    node.left = sortedArrayToBST(array, lo, mid - 1);
    node.right = sortedArrayToBST(array, mid + 1, hi);
    return node;
  }

  public static void main(String[] args) {
    System.out.println("Please run this solution on LeetCode.");
    System.out.println("https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/");
  }
}