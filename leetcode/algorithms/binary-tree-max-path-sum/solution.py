#!/usr/bin/env python


class Solution(object):
    def _maxPathSum(self, root):
        """
        Returns a tuple representing the maximum length of several path types
        within root.

        Type I - Paths starting at root. Can be extended by parents of root.
        Type II - Paths NOT starting at root. These paths might be in the left
                  or right children and not contain root, or in both the left
                  and right children joined by and containing root. These paths
                  cannot be extended by parents of root.
        """
        if root is None:
            return (float('-inf'), float('-inf'))

        left = self._maxPathSum(root.left)
        right = self._maxPathSum(root.right)

        # Calculate max length of Type I path.
        startWithChild = max(left[0], right[0])
        startWithRoot = root.val + max(0, startWithChild)

        # Calculate max length of Type II path. Begin by finding largest path
        # within the child sub-trees.
        withinChildren = max(max(left), max(right))

        # Now try creating a path by joining the two top level paths from the
        # left and right sub-tree with the current node.
        joinWithRoot = root.val + left[0] + right[0]

        # Select the max length Type II path.
        typeTwo = max(withinChildren, joinWithRoot)

        return (startWithRoot, typeTwo)

    def maxPathSum(self, root):
        assert root is not None
        return max(self._maxPathSum(root))


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/binary-tree-maximum-path-sum/')

if __name__ == '__main__':
    main()
