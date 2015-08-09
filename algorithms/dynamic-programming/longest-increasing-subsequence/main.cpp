#include <iostream>

using namespace std;

int* build_sequence(int N) {
    int* sequence = new int[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &sequence[i]);
    }
    return sequence;
}

int tails_ceil(int* tails, int last_index, int replacement) {
    int l = 0, r = last_index, m;
    while (r > l + 1) {
        // This works because len <= 10^6.
        m = (l + r)/2;
        if (tails[m] >= replacement) {
            r = m;
        } else {
            l = m;
        }
    }
    return r;
}

int lis(int* sequence, int N) {
    int* tails = new int[N];
    tails[0] = sequence[0];
    int last_index = 0, existing_index;
    for (int i = 1; i < N; i++) {
        if (sequence[i] <= tails[0]) {
            tails[0] = sequence[i];
        } else if (sequence[i] > tails[last_index]) {
            tails[++last_index] = sequence[i];
        } else {
            existing_index = tails_ceil(tails, last_index, sequence[i]);
            tails[existing_index] = sequence[i];
        }
    }
    return last_index + 1;
}

int main()
{
    int N;
    scanf("%d", &N);
    int* sequence = build_sequence(N);
    printf("%d\n", lis(sequence, N));
    delete [] sequence;
    return 0;
}
