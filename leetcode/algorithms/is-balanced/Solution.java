public class Solution {
  //
  // Checks if the tree rooted at this node is balanced. (If height of left and
  // right sub-tree do not differ in height by more than 1)
  //
  public boolean isBalanced(TreeNode root) {
    return isBalancedHeight(root) != -1;
  }

  //
  // Returns the height of the tree rooted at this node or -1 if the tree is
  // not balanced.
  //
  public int isBalancedHeight(TreeNode root) {
    if (root == null) {
      return 0;
    }

    // Check if left sub-tree is not balanced
    int leftHeight = isBalancedHeight(root.left);
    if (leftHeight == -1) {
      return -1;
    }

    // Check if right sub-tree is not balanced
    int rightHeight = isBalancedHeight(root.right);
    if (rightHeight == -1) {
      return -1;
    }

    // Check if left and right sub-tree have a height difference > 1
    if (Math.abs(leftHeight - rightHeight) > 1) {
      return -1;
    }

    // Return height of this tree
    return 1 + Math.max(leftHeight, rightHeight);
  }

  public static void main(String[] args) {
    System.out.println("Please run this solution on LeetCode.");
    System.out.println("https://leetcode.com/problems/balanced-binary-tree/");
  }
}