#!/usr/bin/env python

import sys


def factorial(n):
    """
    Naively calculates n!
    """
    f = 1
    while n > 0:
        f *= n
        n -= 1
    return f


def count(values):
    """
    Returns a dict of counts for each value in the iterable.
    """
    counts = dict()
    for v in values:
        if v not in counts:
            counts[v] = 0
        counts[v] += 1
    return counts


def rank(word, i, chars):
    """
    Finds the rank of word[i:] amongs permutations of characters in words[i:].

    :type word: str
    :type i: int
    :type chars: Dict[chr, int] The count of each character in word[i:]
    """
    n = len(word)
    assert i >= 0
    assert i < n
    if i == n - 1:
        return 0

    # The first character of the word[i:].
    c = word[i]

    # The number of characters less than word[i] in word[i:]. Helps count the
    # number of words starting with a character less than word[i].
    lt = 0
    for j in range(i, n):
        k = word[j]
        if k < c:
            lt += 1

    # Count the number of words starting with a character less than word[i].
    r = lt * factorial(n - i - 1)

    # Remove identical permutations from duplicate characters.
    for k in chars:
        r /= factorial(chars[k])

    # Recurse for word[i + 1:].
    chars[c] -= 1
    r = int(r) + rank(word, i + 1, chars)
    chars[c] += 1
    return r


def main():
    T = int(sys.stdin.readline())
    for _ in range(0, T):
        word = sys.stdin.readline().strip()
        chars = count(word)
        print(rank(word, 0, chars) + 1)

if __name__ == '__main__':
    main()
