#!/usr/bin/env python


class Solution(object):
    def _count(self, string):
        """
        Returns a dictionary of characters counts in the string.
        """
        count = dict()
        for c in string:
            if c not in count:
                count[c] = 0
            count[c] += 1
        return count

    def minWindow(self, string, target):
        """
        Returns the minimum length window in the string that contains all the
        characters in the target.
        """
        # The char counts in the target string.
        required = self._count(target)

        # The counts of required chars in the current window.
        current = {c: 0 for c in required}

        # The number of unique chars in the current dict that have a count
        # >= to the count of the char in the target string.
        fulfilled = 0

        window = ""
        start = 0

        for i in range(0, len(string)):
            c = string[i]

            # Increment the count of the current character if it is required.
            if c in current:
                current[c] += 1
                # If we have ran into c enough times add if to the fulfilled
                # set of characters.
                if current[c] == required[c]:
                    fulfilled += 1

            # Slide forward the start of the window until we no longer have all
            # the characters in the target string.
            while start <= i and fulfilled == len(required):
                # Check if the this window is shorter than the current result.
                length = i - start + 1
                if len(window) == 0 or length < len(window):
                    window = string[start:i + 1]

                # Discard the character at the start of the window.
                r = string[start]
                if r in current:
                    current[r] -= 1
                    # Check if the character no longer occurs as many times as
                    # it does in the target string.
                    if current[r] == required[r] - 1:
                        fulfilled -= 1

                # Slide the window forard.
                start += 1

        return window


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/minimum-window-substring/')

if __name__ == '__main__':
    main()
