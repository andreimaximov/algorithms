#!/usr/bin/env python


class Solution(object):
    def inorder(self, root):
        """
        Returns the inorder traversal of nodes in the tree.
        """
        current = root
        stack = []
        inorder = []

        while current is not None or len(stack) > 0:
            # Traverse to the left most (first) node in the tree rooted at the
            # current node.
            while current is not None:
                stack.append(current)
                current = current.left

            # The stack is guaranteed to have at least one node due to the
            # condition of the outer while loop.
            current = stack.pop()
            inorder.append(current)

            # Current might be None after this, but then the algorithm will
            # just continue traversing up.
            current = current.right

        return inorder

    def findOutOfOrder(self, root):
        """
        Finds the first two out of order nodes in a binary tree.
        """
        inorder = self.inorder(root)

        # Impossible for any values to be out of order with 0 or 1 nodes.
        if len(inorder) < 2:
            return ()

        outOfOrder = []  # Stores indices where inorder[i] >= inorder[i + 1]
        for i in range(0, len(inorder) - 1):
            if inorder[i].val >= inorder[i + 1].val:
                outOfOrder.append(i)
            if len(outOfOrder) == 2:
                break

        n = len(outOfOrder)
        if n == 0:
            # No out of order nodes.
            return ()
        elif n == 1:
            # Out of order nodes are next to each other.
            i = outOfOrder[0]
            return (inorder[i], inorder[i + 1])
        elif n == 2:
            # Out of order nodes are not next to each other.
            i = outOfOrder[0]
            j = outOfOrder[1]
            return (inorder[i], inorder[j + 1])

    def recoverTree(self, root):
        nodes = self.findOutOfOrder(root)
        assert len(nodes) == 2

        # Swap the values in the two out of order nodes.
        firstValue = nodes[0].val
        nodes[0].val = nodes[1].val
        nodes[1].val = firstValue


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/recover-binary-search-tree/')

if __name__ == '__main__':
    main()
