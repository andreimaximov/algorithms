#!/usr/bin/env python3


def manachers(S):
    """Runs Manachers algorithm on string S.

    Returns an array P where P[i] is the length of the longest substring
    mirrored around i in S. Strictly, S[i - P[i] + 1:i] == S[i + 1:i + P[i]].
    """
    n = len(S)

    assert n > 0

    P = [1] * n

    # Center of the "current" palindrome. This is the palindrome with the
    # furthest reach to the right. (Part of string we haven't calculated P for
    # yet)
    center = 0

    for i in range(1, n):
        if i < center + P[center]:
            # Mirror of i around center
            k = center - (i - center)

            # Estimate a lower bound on P[i]. This is min(P[k], l) where
            # l = center - radius - k + 1. This is the distance from k to the
            # left bound of the "current palindrome". Beyond this bound the
            # the characters may not match on the left and right side so we
            # need to explore further.
            P[i] = min(P[k], k - (center - P[center]))

        while i - P[i] >= 0 and i + P[i] < n and \
                S[i - P[i]] == S[i + P[i]]:
                P[i] += 1

        if i + P[i] > center + P[center]:
            center = i

    return P


def longest_palindrome(S, separator='|'):
    """Returns the longests palindrome in S."""
    assert len(separator) == 1

    if len(S) < 2:
        return str(S)

    X = separator + separator.join(S) + separator
    P = manachers(X)

    # The center and length in X of the longest palindrome. Remember that even
    # indices in X are virtual centers between characters in S.
    center = 0

    # The length of the palindrome in S at position i in X is easy to handle.
    # For odd positions (real character centers) it is 1 + 2 * (P[i] - 2) // 2
    # = P[i] - 1. For even indices (between characters) it is
    # 2 * (P[i] - 1) // 2 = P[i] - 1 as well.
    for i in range(1, len(P)):
        if P[i] > P[center]:
            center = i

    # Extract the actual substring.
    begin = center // 2 - (P[center] - 1) // 2
    return S[begin:begin + P[center] - 1]


def main():
    print('Begin tests...')

    assert longest_palindrome('') == ''
    assert longest_palindrome('a') == 'a'
    assert longest_palindrome('aa') == 'aa'
    assert longest_palindrome('454abcba121') == 'abcba'
    assert longest_palindrome('aba1234321bcdedcb') == '1234321'

    print('Tests pass!')

if __name__ == '__main__':
    main()
