import java.util.HashMap;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class Solution {
  public TreeNode buildTree(int[] preorder, int[] inorder) {
    if (preorder == null || inorder == null || preorder.length != inorder.length) {
      throw new IllegalArgumentException(
          "preorder and inorder must be non-null and same length.");
    }
    return buildTree(preorder, 0, preorder.length - 1, inorder, 0, inorder.length - 1);
  }

  //
  // Builds a tree using preorder[pStart:pEnd + 1] and inorder[iStart:iEnd + 1].
  //
  private TreeNode buildTree(int[] preorder, int pStart, int pEnd,
                             int[] inorder, int iStart, int iEnd) {
    // Check if preorded and inorder sub-lists are empty.
    if (pStart > pEnd) {
      return null;
    }

    // The first element in preorder is a root.
    TreeNode root = new TreeNode(preorder[pStart]);

    // Check if there are any nodes left.
    if (pStart == pEnd) {
      return root;
    }

    // Find where the root value occurs in the inorder traversal.
    int i = find(inorder, iStart, iEnd, root.val);
    assert i != -1;

    // Split left and right side to solve recursively.
    int leftSize = i - iStart;
    root.left = buildTree(preorder, pStart + 1, pStart + leftSize,
                          inorder, iStart, i - 1);
    root.right = buildTree(preorder, pStart + 1 + leftSize, pEnd,
                           inorder, i + 1, iEnd);
    return root;
  }

  //
  // Returns the index i where value occurs in order[start:end + 1] or -1 if
  // the value does not exist.
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
    System.out.println("https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/");
  }
}
