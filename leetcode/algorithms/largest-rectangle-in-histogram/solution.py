#!/usr/bin/env python


class Solution(object):
    def largestRectangleArea(self, heights):
        assert isinstance(heights, list)

        # Index of the current height being processed.
        i = 0

        # Stack of height indexes in order of occurence and non-decreasing
        # height.
        history = []

        maxArea = 0

        def lastIndexIsHeight(right):
            """
            Calculates the maximum area of a rectangle where the height is
            determined by the last height in the history. Uses the specified
            right bound to derive the rectangle width.
            """
            height = heights[history.pop()]

            # Left side of rectangle is either (1) the left side of the entire
            # height list or (2) the last element before it that has a smaller
            # height.
            left = -1

            if len(history) > 0:
                # Index of last height before the one we just popped that had
                # an equal or lower height.
                left = history[-1]

            width = right - left - 1
            return max(maxArea, width * height)

        # Maintain invariant that history is always a stack of bar indexes in
        # order of occurence and non-decreasing height.
        while i < len(heights):
            if len(history) == 0 or heights[history[-1]] <= heights[i]:
                history.append(i)
                i += 1
            else:
                # If this bar is lower height than a previous bar, use previous
                # bar as rectangle height and this index as right side boundary
                # for rectangle.
                maxArea = lastIndexIsHeight(i)

        # Process remaining bars as smallest bars and thus using end of height
        # sequence as boundary for right side of area rectangle.
        right = len(heights)
        while len(history) > 0:
            maxArea = lastIndexIsHeight(right)

        return maxArea


def test(heights, area):
    sol = Solution()
    actual = sol.largestRectangleArea(heights)
    try:
        assert area == actual
    except AssertionError:
        print('Expected %d but got %s.' % (area, actual))
        raise


def main():
    test([], 0)
    test([2], 2)
    test([1, 2, 3], 4)
    test([3, 4, 5, 1, 2], 9)
    print('Tests pass!')
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/largest-rectangle-in-histogram/')


if __name__ == "__main__":
    main()
