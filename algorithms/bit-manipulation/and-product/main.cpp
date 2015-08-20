#include <iostream>
#include <cmath>

using namespace std;

typedef unsigned long int uli;

uli and_product(uli A, uli B)
{
    int floor_p2 = (int) log2(A), ceil_p2 = (int) log2(B);
    if (ceil_p2 >= floor_p2 + 1) {
        return 0;
    }
    uli product = A;
    while (A < B) {
        A++;
        product = product & A;
    }
    return product;
}

int main()
{
    int T;
    uli A, B;
    scanf("%d", &T);
    while (T--) {
        scanf("%ld%ld", &A, &B);
        printf("%ld\n", and_product(A, B));
    }
    return 0;
}
