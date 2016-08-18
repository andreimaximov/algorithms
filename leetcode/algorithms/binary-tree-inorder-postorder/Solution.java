import java.util.ArrayList;
import java.util.List;

public class Solution {
  public TreeNode buildTree(int[] inorder, int[] postorder) {
    if (inorder == null || postorder == null
        || inorder.length != postorder.length) {
      throw new IllegalArgumentException(
          "inorder and postorder must be non-null and same length.");
    }
    return buildTree(inorder, 0, inorder.length - 1,
                     postorder, 0, postorder.length - 1);
  }

  //
  // Builds a tree using inorder[iStart:iEnd + 1] and
  // postorder[pStart:pEnd + 1].
  //
  private TreeNode buildTree(int[] inorder, int iStart, int iEnd,
                             int[] postorder, int pStart, int pEnd) {
    // Check if inorder and postorder sub-lists are empty.
    if (pStart > pEnd) {
      return null;
    }

    // The last element in postorder is a root.
    TreeNode root = new TreeNode(postorder[pEnd]);

    // Check if there are any nodes left.
    if (pStart == pEnd) {
      return root;
    }

    // Find where the root value occurs in the inorder traversal.
    int i = find(inorder, iStart, iEnd, root.val);
    assert i != -1;

    // Split left and right side to solve recursively.
    int leftSize = i - iStart;
    root.left = buildTree(inorder, iStart, i - 1,
                          postorder, pStart, pStart + leftSize - 1);
    root.right = buildTree(inorder, i + 1, iEnd,
                           postorder, pStart + leftSize, pEnd - 1);
    return root;
  }

  //
  // Returns the index i where value occurs in order[start:end + 1] or
  // -1 if the value does not exist.
  //
  private int find(int[] order, int start, int end, int value) {
    for (int i = start; i <= end; i++) {
      if (order[i] == value) {
        return i;
      }
    }
    return -1;
  }

  public static void main(String[] args) {
    System.out.println("Please run this solution on LeetCode.");
    System.out.println("https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/");
  }
}
