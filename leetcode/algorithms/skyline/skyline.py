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

    def cleanSkyline_(self, skyline):
        """
        Cleans the skyline by removing redundant points.

        :type skyline: List[(int, int)]
        :rtype: List[(int, int)]
        """

        if len(skyline) == 0:
            return list()

        # Initialize clean skyline
        clean = [skyline[0]]

        for i in range(1, len(skyline)):
            # Check if two points share vertical
            if skyline[i][0] == clean[-1][0]:
                # Grab highest y coordinate
                y = max(skyline[i][1], clean[-1][1])
                clean[-1] = (clean[-1][0], y)
            # Check if two points share horizontal
            elif skyline[i][1] == clean[-1][1]:
                # Grab left most x coordinate
                x = min(skyline[i][0], clean[-1][0])
                clean[-1] = (x, clean[-1][1])
            # Otherwise just append this point
            else:
                clean.append(skyline[i])

        return clean

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

        # Traverse points from left to right
        while l < len(left) and r < len(right):
            point = None

            if left[l][0] < right[r][0]:  # Next point is in left skyline
                lh = left[l][1]
                h = max(lh, rh)
                point = (left[l][0], h)
                l += 1
            elif left[l][0] > right[r][0]:  # Next point is in right skyline
                rh = right[r][1]
                h = max(lh, rh)
                point = (right[r][0], h)
                r += 1
            else:  # Next points have same x coordinate (Share vertical edge)
                lh = left[l][1]
                rh = right[r][1]
                h = max(lh, rh)
                point = (right[r][0], h)
                l += 1
                r += 1

            skyline.append(point)

        # Append left-over points
        skyline.extend(left[l:])
        skyline.extend(right[r:])

        return self.cleanSkyline_(skyline)

    def getSkyline_(self, buildings, lo, hi):
        """
        :type buildings: List[List[int]]
        :type lo: int
        :type hi: int
        :rtype: List[(int, int)]
        """
        if lo == hi:
            # Return countour for a single building
            building = buildings[lo]
            return [(building[0], building[2]), (building[1], 0)]

        # Solve left and right sub-problems separately
        mid = lo + int((hi - lo) / 2)
        left = self.getSkyline_(buildings, lo, mid)
        right = self.getSkyline_(buildings, mid + 1, hi)

        # Merge solutions
        return self.mergeSkylines_(left, right)


def main():
    solution = Solution()
    assert solution.getSkyline(TEST_BUILDINGS) == TEST_SKYLINE

    print('Tests pass!')
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/the-skyline-problem/')


if __name__ == "__main__":
    main()
