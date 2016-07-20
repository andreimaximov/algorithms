import java.util.Stack;

public class Solution {
  //
  // This is a BFS algorithms that checks if the tree rooted at the given node
  // is a valid BST.
  //
  public boolean isValidBST(TreeNode root) {
    if (root == null) {
        return true;
    }
    Integer prev = null;
    TreeNode curr = root;
    Stack<TreeNode> stack = new Stack<>();
    while (!stack.isEmpty() || curr != null) {
      // Continue all the way down the left...
      while (curr != null) {
        stack.push(curr);
        curr = curr.left;
      }
      curr = stack.pop();
      // Check if the current node violates BFS rule...
      if (prev != null && curr.val <= prev) {
        return false;
      }
      // Take the right branch...
      prev = curr.val; // The prev is now the value at the current node...
      curr = curr.right; // Might be null but ok if stack is not empty...
    }
    return true;
  }

  public static void main(String[] args) {
    System.out.println("Please run this solution on LeetCode.");
    System.out.println("https://leetcode.com/problems/validate-binary-search-tree/");
  }
}
