TEST_BUILDINGS = [
    [2, 9, 10],
    [3, 7, 15],
    [5, 12, 12],
    [15, 20, 10],
    [19, 24, 8]
]

TEST_SKYLINE = [
    (2, 10),
    (3, 15),
    (7, 12),
    (12, 0),
    (15, 10),
    (20, 8),
    (24, 0)
]


class Solution(object):
    def getSkyline(self, buildings):
        """
        :type buildings: List[List[int]]
        :rtype: List[(int, int)]
        """
        if len(buildings) == 0:
            return list()

        return self.getSkyline_(buildings, 0, len(buildings) - 1)

    def getSkyline_(self, buildings, lo, hi):
        """
        :type buildings: List[List[int]]
        :type lo: int
        :type hi: int
        :rtype: List[(int, int)]
        """
        assert lo >= 0
        assert hi < len(buildings)
        assert lo <= hi

        if lo == hi:
            # Return countour for a single building
            b = buildings[lo]
            return [(b[0], b[2]), (b[1], 0)]

        # Solve left and right sub-problems separately
        mid = lo + (hi - lo) // 2
        left = self.getSkyline_(buildings, lo, mid)
        right = self.getSkyline_(buildings, mid + 1, hi)

        # Merge solutions
        return self.mergeSkylines_(left, right)

    def mergeSkylines_(self, left, right):
        """
        :type left: List[(int, int)]
        :type right: List[(int, int)]
        :rtype: List[(int, int)]
        """
        if len(left) == 0:
            return right
        elif len(right) == 0:
            return left

        l = 0   # Current point on left skyline
        r = 0   # Current point on right skyline
        lh = 0  # Last height of left skyline
        rh = 0  # Last height of right skyline

        skyline = list()

        def add(x, height):
            if len(skyline) > 0 and skyline[-1][1] == height:
                return
            skyline.append((x, height))

        # Traverse skylines in paralle from left to right.
        while l < len(left) or r < len(right):
            if r >= len(right) or l < len(left) and left[l][0] < right[r][0]:
                # Either we are done with the right skyline or the next point
                # on the left is before the next point on the right.
                lh = left[l][1]
                x = left[l][0]
                l += 1
            elif l >= len(left) or r < len(right) and left[l][0] > right[r][0]:
                # Either we are done with the left skyline or the next point on
                # the right is before the next point on the left.
                rh = right[r][1]
                x = right[r][0]
                r += 1
            else:
                # Next points in each skyline have same x.
                lh = left[l][1]
                rh = right[r][1]
                x = left[l][0] if l < len(left) else right[r][0]
                l += 1
                r += 1

            add(x, max(lh, rh))

        return skyline


def main():
    solution = Solution()
    assert solution.getSkyline(TEST_BUILDINGS) == TEST_SKYLINE

    print('Tests pass!')
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/the-skyline-problem/')


if __name__ == "__main__":
    main()
