#!/usr/bin/env python


class Solution(object):
    def detectCycle(self, head):
        """
        Given the head of a linked list finds and returns the node where a
        cycle begins. Uses O(1) space and O(N) time.

        Imagine the list is made up of two parts. The first part before the
        the cycle is of length K followed by cycle length N. If we place a slow
        and fast (double speed) pointer at the head of the list, the fast
        pointer will be N % K nodes into the cycle when the slow pointer
        reaches the start of the cycle.

        This means that the slow pointer is N % K nodes behind the fast pointer
        and N - (N % K) nodes ahead of it. Thus the pointers will collide
        N - (N % K) nodes into the cycle.

        When they collide, we place one of the pointers back to the head and
        increment both pointers at normal speed. They will collide at the
        start of the cycle. This is because it will take the pointer now at
        the head K turns to get to the start of the cycle at which point the
        other pointer will be at position N % (N - N % K + K) = 0 in the cycle
        as well.
        """
        slow = head
        fast = head

        # Move pointers until we reach end of cycle or pointers collide.
        while fast is not None and fast.next is not None:
            slow = slow.next
            fast = fast.next.next
            if slow == fast:
                break

        # Take care of case with no cycle.
        if fast is None or fast.next is None:
            return None

        # Now move one pointer back to head and iterate one node at a time.
        slow = head
        while slow != fast:
            slow = slow.next
            fast = fast.next

        return slow


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/linked-list-cycle-ii/')

if __name__ == '__main__':
    main()
