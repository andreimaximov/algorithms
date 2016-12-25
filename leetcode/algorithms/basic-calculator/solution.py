#!/usr/bin/env python

import operator


class Solution(object):
    OPS = {'+': operator.add, '-': operator.sub}

    def calculate(self, s):
        """Calculates the expression s.

        Args:
            s (str): The arithmetic expression with +, -, (, and ) symbols.

        Returns:
            int: The value of the calculated expression.
        """
        # Surround the expression in parenthesis so the entire thing is
        # evaluated.
        tokens = self.parse('(%s)' % s)
        result, _ = self.eval(tokens, 1)
        return result

    def parse(self, s):
        """Parses expression s into a list of tokens.

        Args:
            s (str): The expression to parse.

        Returns:
            List[str]: List of int, operator, and parenthesis tokens.
        """
        s = s = ''.join(s.split())
        n = len(s)
        start = -1
        tokens = []

        for i in range(n):
            if s[i].isdigit():
                if start == -1:
                    start = i
            else:
                if start != -1:
                    tokens.append(int(s[start:i]))
                    start = -1
                tokens.append(s[i])

        # Don't forget trailing int!
        if start != -1:
            tokens.append(int(s[start:]))

        return tokens

    def eval(self, tokens, i):
        """Evaluates the first expression in tokens[i:] until it reaches a
           closing parenthesis without a corresponding opening parenthesis.

        Args:
            tokens (List[str]): The parsed list of expression tokens.

        Returns:
            (int, int): (result, cursor) tuple where cursor is the index of
                        the first token after this expression. Usually the
                        terminating closing parenthesis.
        """
        n = len(tokens)

        # Process the first token.
        if tokens[i] == '(':
            result, j = self.eval(tokens, i + 1)
            assert j < n and tokens[j] == ')'

            # Terminate if this is a single token expression.
            if j == n - 1 or tokens[j + 1] == ')':
                return result, j + 1

            x = result
            j += 1
        else:
            x = tokens[i]
            j = i + 1

        assert type(x) is int
        result = x

        # Continue extracting tokens until we reach end of expression.
        while j < n and tokens[j] in Solution.OPS:
            op = Solution.OPS[tokens[j]]
            y = tokens[j + 1]
            if y == '(':
                y, j = self.eval(tokens, j + 2)
                j += 1
            else:
                j += 2
            result = op(result, y)

        return result, j


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/basic-calculator/')

if __name__ == '__main__':
    main()
