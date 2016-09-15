#!/usr/bin/env python


class Solution(object):
    def maxArea(self, heights):
        """
        Given a list of line heights, finds the largest container between two
        lines. Good explanation of the algorithm can be found at
        https://discuss.leetcode.com/topic/3462/yet-another-way-to-see-what-happens-in-the-o-n-algorith # nopep8
        """
        n = len(heights)
        if n < 2:
            return 0

        maxArea = 0
        left = 0
        right = n - 1

        while (left < right):
            # Calculate the area for this pair of left/right lines and check if
            # this is a new maximum area.
            h = min(heights[left], heights[right])
            area = h * (right - left)
            maxArea = max(maxArea, area)

            if heights[left] < heights[right]:
                # If right line is higher than left line, there is no right
                # line further from the left than the current one.
                left += 1
            elif heights[right] < heights[left]:
                # If left line is higher than right line, there is no left
                # line further from the right than the current one.
                right -= 1
            else:
                # If both the left and right lines are the same height, then
                # both of the above cases hold.
                left += 1
                right -= 1

        return maxArea


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/container-with-most-water/')

if __name__ == '__main__':
    main()
