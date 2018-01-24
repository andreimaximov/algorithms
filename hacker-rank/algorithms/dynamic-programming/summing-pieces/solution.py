import sys

MOD = 1000000007


def mul(a, b):
    """Returns the modulo multiplication of a and b."""
    return (a * b) % MOD


def add(a, b):
    """Returns the module sum of a and b."""
    return (a + b) % MOD


def pieces(A):
    """Calculates the sum of all B that form A in O(n) time and O(1) space.

    We build the solution from a base case when len(A) = 1 and continuously
    append A[i] to the result computed for each A[0...i - 1]. We use the
    following 4 variables.

    x(i) = The solution for A[0...i]
    y(i) = The number of unique arrangements of pieces that form A[0...i]
    s(i) = The set of suffix pieces across all unique arrangements that form
           A[0...i]
    k(i) = The sum of lengths of all s(i)
    m(i) = The sum of values in all s(i)

    Call dp(i) = (x(i), y(i), k(i), m(i))

    For n = 1 we say dp(0) = (A[0], 1, 1, A[0]). Now, how do we go from dp(i)
    to dp(i + 1)?

    There are two ways we can append A[i + 1] to the solution for A[0...i].

    1) We can append another piece (A[i + 1]) to all combinations of pieces
    that formed A[0...i].

    2) Or we can append A[i + 1] to the suffix pieces that formed A[0...i].

    To calculate x(i + 1) from x(i) we also need k(i) and m(i). See code
    comments for details on how to handle each case.

    Lastly, each time we are doubling the number of unique piece combinations
    that form A[i...n] so y(i + 1) = 2 * y(i).

    Args:
        A (List[int])

    Returns:
        int
    """
    n = len(A)
    if n == 0:
        return 0

    # DP represents the 4 variables x, y, z, a for each i
    dp = A[0], 1, 1, A[0]

    for i in range(1, n):
        last_x, last_y, last_k, last_m = dp

        # Case 1 - Append a piece (A[i])
        exc_x = add(last_x, mul(A[i], last_y))

        # Case 2 - The essence here is that existing suffix pieces increase
        # in length by one which affects by how much A[i] is factored in and
        # that the value of each piece increases by m(i).
        inc_x = add(last_x,
                    add(last_m,  # Prefix piece increases in value my m(i + 1)
                        mul(A[i], add(last_k, last_y))))  # Factor in A[i]
        x = add(exc_x, inc_x)

        # Double combinations
        y = mul(last_y, 2)

        # k(i) = k(i + 1) + y(i + 1) * 2 = k(i + 1) + y(i)
        k = add(last_k, y)

        # m(i) = A[i] * y(i) + m(i + 1)
        m = add(mul(A[i], y), last_m)

        dp = x, y, k, m

    # Return x(0)
    return dp[0]


def main():
    n = int(sys.stdin.readline())
    A = [int(x) for x in sys.stdin.readline().split()]
    print(pieces(A))


if __name__ == '__main__':
    main()
