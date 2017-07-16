#!/usr/bin/env python3


def kmp(S):
    """Runs the Knuth-Morris-Pratt algorithm on S.

    Returns a table F such that F[i] is the longest proper suffix of S[0...i]
    that is also a prefix of S[0...i].
    """
    n = len(S)

    if n == 0:
        return []

    F = [0] * n

    for i in range(1, n):
        k = F[i - 1]

        while k > 0 and S[k] != S[i]:
            k = F[k - 1]

        if S[k] == S[i]:
            k += 1

        F[i] = k

    return F


def find(T, P, separator='#'):
    """Returns a list of indexes in T where full occurences of P begin."""
    S = P + separator + T
    F = kmp(S)
    return [i - 2 * len(P) for i in range(len(F)) if F[i] == len(P)]


def main():
    print('Begin tests...')

    assert find('a', 'a') == [0]
    assert find('sadasda', 'sda') == [4]
    assert find('rishrisrishirishirishrishiririshi', 'rishi') == \
        [7, 12, 21, 28]
    assert find('aaaa', 'aa') == [0, 1, 2]
    assert find('AABAACAADAABAABA', 'AABA') == [0, 9, 12]
    assert find('THIS IS A TEST TEXT', 'TEST') == [10]

    print('Tests pass!')

if __name__ == '__main__':
    main()
