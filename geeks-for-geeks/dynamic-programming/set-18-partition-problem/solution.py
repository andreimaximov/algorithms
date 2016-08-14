#!/usr/bin/env python

TEST_INPUT = [
    [],
    [1],
    [1, 2],
    [1, 2, 3],
    [1, 2, 3, 4],
    [1, 2, 3, 4, 5],
    [1, 2, 3, 4, 5, 6]
]

TEST_OUTPUT = [
    True,
    False,
    False,
    True,
    True,
    False,
    False
]


def subset_sum(nums, hi, sum, dp):
    """
    Returns a bool indicating if nums[0:hi + 1] has a subset with the specified
    sum. DP[i][j] stores bool indicating if nums[0:i + 1] has a subset with sum
    j.
    """

    if hi == 0:
        # Check only element.
        return nums[0] == sum
    elif sum in dp[hi]:
        # Return cached result.
        return dp[hi][sum]

    # Include the last element in the subset.
    has_subset = subset_sum(nums, hi - 1, sum - nums[hi], dp)
    if not has_subset:
        # Exclude the last element in the subset.
        has_subset = subset_sum(nums, hi - 1, sum, dp)

    # Cache result and return.
    dp[hi][sum] = has_subset
    return has_subset


def list_partitionable(nums):
    """
    Returns a bool indicating if nums can be partitioned into two lists with
    equal sums.
    """

    n = len(nums)
    if n == 0:
        return True
    elif n == 1:
        return False

    sum = 0
    for i in nums:
        sum += i

    # Sum must be even so that each subset has sum of sum / 2.
    if sum % 2 != 0:
        return False

    # DP[i][j] stores bool indicating if nums[0:i + 1] has a subset with sum j.
    dp = [dict() for i in range(0, n)]
    return subset_sum(nums, n - 1, sum / 2, dp)


def main():
    for i in range(0, len(TEST_INPUT)):
        print("Running test case %d..." % (i + 1))
        assert TEST_OUTPUT[i] == list_partitionable(TEST_INPUT[i])

    print("Tests pass!")


if __name__ == "__main__":
    main()
