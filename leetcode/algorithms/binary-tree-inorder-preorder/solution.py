#!/usr/bin/env python


class Solution(object):
    def _buildTree(self, preorder, i, j, inorder, k, l, index):
        """
        Builds a tree using the specified preorder[i:j + 1] and
        inorder[k:l + 1] traversals.

        :type preorder: List[int]
        :type i: int The start index of the preorder slice we are building.
        :type j: int The end index of the inorder slice we are building.
        :type inorder: List[int]
        :type k: int The start index of the inorder slice we are building.
        :type l: int The end index of the inorder slice we are building.
        :type index: Dict[int, int] Map from each value in the inorder
                                    traversal to its index.
        :rtype: TreeNode
        """
        n = j - i + 1
        m = l - k + 1

        # Ensures that the lists are not empty and the same size.
        assert n > 0
        assert m > 0
        assert n == m

        # Create the root node using the first value in the preorder slice.
        value = preorder[i]
        root = TreeNode(value)

        # Find where this value occurs in the inorder traversal.
        x = index[value]

        # Calculate the number of left children this root has.
        left = x - k

        # Create the left sub-tree if there is at least one left child.
        if x > k:
            root.left = self._buildTree(preorder, i + 1, i + left,
                                        inorder, k, x - 1, index)
        # Create the right sub-tree if there is at least one right child.
        if x < l:
            root.right = self._buildTree(preorder, i + left + 1, j,
                                         inorder, x + 1, l, index)

        return root

    def buildTree(self, preorder, inorder):
        """
        Builds a tree with the specified preorder and inorder traverals.

        :type preorder: List[int]
        :type inorder: List[int]
        :rtype: TreeNode
        """
        n = len(preorder)
        m = len(inorder)

        assert n >= 0
        assert m >= 0
        assert n == m

        # Take care of the empty tree case.
        if n == 0:
            return None

        # Build an index/map from values in the inorder traversal to the index
        # of each value.
        index = {}
        for i in range(0, m):
            index[inorder[i]] = i

        return self._buildTree(preorder, 0, n - 1, inorder, 0, m - 1, index)


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/')  # nopep8

if __name__ == '__main__':
    main()
