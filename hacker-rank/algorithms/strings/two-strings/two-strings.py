#!/usr/bin/env python

import sys


def char_set(string):
    chars = {}
    for c in string:
        chars[c] = True
    return chars


def test_case():
    A = sys.stdin.readline().strip()
    B = sys.stdin.readline().strip()
    bCharSet = char_set(B)
    for c in A:
        if (c in bCharSet):
            print("YES")
            return
    print("NO")


def main():
    T = int(sys.stdin.readline())
    while (T > 0):
        test_case()
        T -= 1

if __name__ == '__main__':
    main()
