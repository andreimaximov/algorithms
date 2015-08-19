#include <iostream>
#include <cmath>

using namespace std;

long long first_k(int N, int K)
{
    long double f = N * log10(2.0L);
    f -= (int) f;
    f = pow(10.0, f);
    f *= pow(10, K - 1);
    return f;
}

long long last_k(int N, int mod)
{
    if (N == 0) {
        return 1;
    } else if (N % 2 == 0) {
        long long mod_root = last_k(N / 2, mod) % mod;
        return (mod_root * mod_root) % mod;
    } else {
        return (2 * last_k(N - 1, mod)) % mod;
    }
}

int main()
{
    int T, N, K;
    scanf("%d", &T);
    while (T > 0) {
        scanf("%d%d", &N, &K);
        printf("%lld\n", first_k(N - 1, K) + last_k(N - 1, (int) pow(10, K)));
        --T;
    }
    return 0;
}
