#!/usr/bin/env python


DEBUG = False


def log(message, args=()):
    if DEBUG:
        print(message % args)


class Solution(object):
    def _int(self, string, i):
        """
        Parses a single positive or negative integer in the string starting at
        index i. Returns a tuple with the parsed integer and the index where
        parsing terminated.
        """
        assert i >= 0
        assert i < len(string)

        sign = -1 if string[i] == '-' else 1
        start = i + 1 if string[i] == '-' else i  # Skip the '-' character.
        i = start

        # Find the end of the integer we are parsing.
        while i < len(string) and string[i].isdigit():
            i += 1

        assert start < i, \
            'int parse error: character %s at position %d' % (string[i], i + 1)

        value = int(string[start:i]) * sign
        log('returning int parse result (%d, %d)', (value, i))
        return (value, i)

    def _list(self, string, i):
        """
        Parses a list in the string starting at index i. Returns a tuple with
        the parsed list and the index where parsing terminated.
        """
        assert i >= 0
        assert i < len(string)

        # Ensure this is the start of a list.
        assert string[i] == '['
        i += 1

        result = []

        while i < len(string) and string[i] != ']':
            (value, i) = self._parse(string, i)
            result.append(value)

            assert i < len(string), 'list parse error: unterminated list'
            if i == len(string) - 1:
                assert string[i] == ']', 'list parse error: unterminated list'

            if string[i] == ']':
                continue

            # Ensure the next token is a list item separator.
            assert string[i] == ',', \
                'list parse error: expected "," but got %s at position %d' % \
                (string[i], i + 1)
            i += 1

        log('returning list parse result (%s, %d)', (result, i))
        return (result, i + 1)

    def _parse(self, string, i):
        """
        Parses the string starting at index i. Returns a tuple with the parsed
        value and the index where parsing terminated.
        """
        assert i >= 0
        assert i < len(string)
        if string[i] == '[':
            return self._list(string, i)
        elif string[i].isdigit() or string[i] == '-':
            return self._int(string, i)
        assert False, 'parse error: unexpected character %s at position %d' % \
            (string[i], i + 1)

    def deserialize(self, string):
        assert len(string) > 0
        (value, i) = self._parse(string, 0)

        # Ensure the entire string was parsed.
        assert i == len(string), \
            'parse error: position %d character %s' % (i, string[i])

        return NestedInteger(value)


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/mini-parser/')

if __name__ == '__main__':
    main()
