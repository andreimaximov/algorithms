#!/usr/bin/env python

import operator


class Solution(object):
    OPS = {'+': operator.add, '-': operator.sub, '*': operator.mul}

    def _parse(self, input):
        """
        Parses the string expression into a list of integers and function
        operators.
        """
        tokens = []
        start = 0

        for i in range(1, len(input)):
            c = input[i]
            if c in Solution.OPS:
                tokens.append(int(input[start:i]))
                tokens.append(Solution.OPS[c])
                start = i + 1

        tail = int(input[start:])
        tokens.append(tail)

        return tokens

    def _diffWaysToCompute(self, tokens, i, j, cache):
        """
        Returns all possible computation results from all possible ways of
        arranging parenthesis around tokens[i:j + 1]. tokens[i] and tokens[j]
        must be numeric constants while all in-between tokens must alternate
        between numeric constants and function operators.

        Splits tokens[i:j + 1] around each operators in the range, computes
        ways for each left and right side, and combines according to the
        operator that the tokens were split around. Uses DP to avoid
        recomputing overlapping sub-problems.
        """
        # The DP indeces for each [i...j] range. For a token array with N
        # numeric constants, there are 2 * N - 1 total tokens because there is
        # an operator between each numeric constant.
        dpi = int(i / 2)
        dpj = int(j / 2)

        if i == j:
            # Single number without any surrounding operators.
            return [tokens[i]]
        elif cache[dpi][dpj] is not None:
            # Reuse previously computed result.
            return cache[dpi][dpj]

        ways = []

        # Step through tokens and split around each operator.
        for k in range(i + 1, j, 2):
            lhs = self._diffWaysToCompute(tokens, i, k - 1, cache)
            rhs = self._diffWaysToCompute(tokens, k + 1, j, cache)
            op = tokens[k]

            # Combine each possible result from the left split with each
            # possible result from the right split.
            for l in lhs:
                for r in rhs:
                    ways.append(op(l, r))

        cache[dpi][dpj] = ways
        return ways

    def diffWaysToCompute(self, input):
        """
        Returns all possible computation results from all possible ways of
        arranging parenthesis in the given input. The input must be a sequence
        of integers separated by the operators +, -, or * and nothing else.
        """
        if len(input) == 0:
            return []
        tokens = self._parse(input)

        # Out of N tokens (N + 1) / 2 are numeric constants. Create a 2D matrix
        # that will serve as a DP cache for each [i...j] range of constants.
        n = int((len(tokens) + 1) / 2)
        cache = [[None for i in range(0, n)] for j in range(0, n)]

        return self._diffWaysToCompute(tokens, 0, len(tokens) - 1, cache)


def main():
    sol = Solution()
    actual = set(sol.diffWaysToCompute('2*3-4*5'))
    expected = set([-34, -14, -10, -10, 10])
    try:
        assert actual == expected
    except AssertionError:
        print('Expected %s but got %s.' % (expected, actual))
        raise

    print('Tests pass!')
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/different-ways-to-add-parentheses/')


if __name__ == "__main__":
    main()
