#!/usr/bin/env python


class Solution(object):
    def containsNearbyAlmostDuplicate(self, values, k, t):
        """
        Returns a boolean indicating if there are i and j such that
        abs(i - j) <= k and abs(values[i] - values[j]) <= t in O(n) time.

        :type values: List[int]
        :type k: int
        :type t: int
        :rtype: bool
        """
        if t < 0:
            return False

        n = len(values)
        k = abs(k)

        # Process values in order and dump each one in a bucket. Each bucket
        # has a maximum range t of the elements in the bucket.
        buckets = dict()

        def bucket(x):
            return x // (t + 1)

        for i in range(0, n):
            # Clear out elements that have slid out of the latest k length
            # window.
            if i > k:
                # Since we are still in the loop, that means there was only
                # one value in the same bucket as the tail of the last window.
                # Thus it is safe to delete it without worrying about other
                # values in the window belonging to the same bucket.
                tail = values[i - k - 1]
                del buckets[bucket(tail)]

            current = values[i]
            j = bucket(current)

            # There are 3 buckets we need to look at.
            #
            # 1) j -> Elements in each bucket have a max different of t. Thus
            #    if there is anything else we found a match.
            # 2) j - 1 -> If there is nothing in bucket j, there might be
            #    a match in the previous bucket. We just need to make sure that
            #    the LAST value we saw in bucket j - 1 is within t. More on why
            #    we only care about the LAST value later.
            # 3) j + 1 -> Similar argument as for bucket j - 1.
            #
            # Why do we only care about the LAST value for a bucket? Say we
            # have values[i] = X and values[j] = Y where i < j such that both X
            # and Y map to the same bucket j, abs(X - current) <= t and
            # abs(Y - current) > t. Wouldn't we like to detect the fact that
            # current and X are in range of each other? Nope, because X and Y
            # are in range t of each other in the same bucket which we would
            # have found earlier!
            #
            # Loop invariants, invariants, invariants...
            if j in buckets:
                return True
            elif j - 1 in buckets and abs(current - buckets[j - 1]) <= t:
                return True
            elif j + 1 in buckets and abs(current - buckets[j + 1]) <= t:
                return True

            # Overwrite the value of bucket j with the current value. Why is
            # this safe and why do we not need to track all values from the
            # current window in bucket j? Because there is nothing in bucket j
            # since the if check in the previous section failed!
            buckets[j] = current

        return False


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/contains-duplicate-iii/')

if __name__ == '__main__':
    main()
