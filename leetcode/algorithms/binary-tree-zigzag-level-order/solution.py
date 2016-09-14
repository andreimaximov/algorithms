#!/usr/bin/env python

from collections import deque


class Solution(object):
    ITERATIVE_ALGO = True

    def zigzagLevelOrderRecGather(self, current, levels, reverse):
        """
        Appends the values in the current level to levels and generates the
        next level.
        """
        if len(current) == 0:
            return

        # Gather values from current level and reverse if needed.
        values = list(map(lambda node: node.val, current))
        if reverse:
            values.reverse()
        levels.append(values)

        # Construct next level of nodes.
        nextLevel = []
        for node in current:
            if node.left is not None:
                nextLevel.append(node.left)
            if node.right is not None:
                nextLevel.append(node.right)

        self.zigzagLevelOrderRecGather(nextLevel, levels, not reverse)

    def zigzagLevelOrderRec(self, root):
        """
        Returns a zigsag level order traversal of the tree. (Recursive
        algorithm)

        :type root: TreeNode
        :rtype: List[List[int]]
        """
        if root is None:
            return []
        current = [root]
        levels = []
        self.zigzagLevelOrderRecGather(current, levels, False)
        return levels

    def zigzagLevelOrderIter(self, root):
        """
        Returns a zigzag level order traversal of the tree. (Iterative
        algorithm)

        :type root: TreeNode
        :rtype: List[List[int]]
        """
        if root is None:
            return []

        queue = deque()
        queue.append(root)

        i = 0  # Tracks the current level we are building.
        first = None  # Tracks the first node in the next level.
        current = []  # The current level we are building.
        levels = []  # The result list of zigzag level order traverals.

        def endCurrentLevel():
            if i % 2 == 1:
                current.reverse()
            values = list(map(lambda node: node.val, current))
            levels.append(values)

        while len(queue) > 0:
            node = queue.popleft()

            # Check if this node is the first node in the next level. If so, we
            # need to add the current level to the zigzag traversal result and
            # reset the current level.
            if first == node:
                endCurrentLevel()
                i += 1
                first = None
                current = []

            # Add this node to current level.
            current.append(node)

            # Queue up children for processing.
            if node.left is not None:
                queue.append(node.left)
            if node.right is not None:
                queue.append(node.right)

            # Update the first node in the next level if not determined yet.
            if first is None:
                first = node.left if node.left is not None else node.right

        endCurrentLevel()
        return levels

    def zigzagLevelOrder(self, root):
        if Solution.ITERATIVE_ALGO:
            return self.zigzagLevelOrderIter(root)
        return self.zigzagLevelOrderRec(root)


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/')  # nopep8

if __name__ == '__main__':
    main()
