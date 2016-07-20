import java.util.ArrayList;
import java.util.List;

public class Solution {
  //
  // Finds the LCA of node p and q in the tree. Returns null if p or q is not in
  // the tree.
  //
  public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
    List<TreeNode> pPath = findPath(root, p);
    List<TreeNode> qPath = findPath(root, q);
    int length = Math.min(pPath.size(), qPath.size());
    for (int i = 0; i < length; i++) {
      if (pPath.get(i) != qPath.get(i)) {
        return pPath.get(i - 1);
      }
    }
    return pPath.get(length - 1);
  }

  //
  // Returns a path of nodes from root to target in the tree. The path is empty
  // if target is not in the tree.
  //
  public List<TreeNode> findPath(TreeNode root, TreeNode target) {
    List<TreeNode> path = new ArrayList<>();
    findPathHelper(root, target, path);
    return path;
  }

  //
  // Populates the path list with nodes that represent the path from the root to
  // the target node. Returns a boolean indicating if the target was found in
  // the tree at the specified root.
  //
  public boolean findPathHelper(TreeNode root, TreeNode target, List<TreeNode> path) {
    if (root == null) {
      return false;
    }
    path.add(root);
    if (root == target) {
      return true;
    }
    if (findPathHelper(root.left, target, path)) {
      return true;
    } else if (findPathHelper(root.right, target, path)) {
      return true;
    }
    path.remove(path.size() - 1);
    return false;
  }

  public static void main(String[] args) {
    System.out.println("Please run this solution on LeetCode.");
    System.out.println("https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/");
  }
}
