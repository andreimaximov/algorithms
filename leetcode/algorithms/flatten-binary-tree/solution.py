#!/usr/bin/env python


class Solution(object):
    def flatten(self, root):
        """
        Flattens the tree at the root node into a linked list. The problem
        statement depicts a pre-order flattening which we can do with an
        iterative traversal.

        :type root: TreeNode
        :rtype: None
        """
        if root is None:
            return

        stack = [root]

        # The parent of the top node in the stack. This is the previous node
        # since we are doing a preorder traversal.
        parent = TreeNode(None)

        while len(stack) > 0:
            node = stack.pop()

            # Update previous/parent node with this node as the right child.
            parent.left = None
            parent.right = node
            parent = node

            if node.right is not None:
                stack.append(node.right)

            if node.left is not None:
                stack.append(node.left)


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/flatten-binary-tree-to-linked-list/')

if __name__ == '__main__':
    main()
