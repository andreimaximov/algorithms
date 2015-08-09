#include <iostream>

using namespace std;

int* build_sequence(int length) {
    int* sequence = new int[length];
    for (int i = 0; i < length; i++) {
        cin >> sequence[i];
    }
    return sequence;
}

int** _lcs(int* a, int n, int *b, int m) {
    m++;n++;
    int** cache = new int*[n];
    for (int i = 0; i < n; i++) {
        cache[i] = new int[m];
        for (int j = 0; j < m; j++) {
            if (i == 0 || j == 0) {
                cache[i][j] = 0;
            } else if (a[i - 1] == b[j - 1]) {
                cache[i][j] = cache[i - 1][j - 1] + 1;
            } else {
                cache[i][j] = max(cache[i][j - 1],  cache[i - 1][j]);
            }
        }
    }
    return cache;
}

int* lcs(int* a, int n, int* b, int m) {
    int** cache = _lcs(a, n, b, m);
    int i = n, j = m, index = cache[n][m];

    int* sub_seq = new int[index + 1];
    sub_seq[index] = -1;

    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            sub_seq[--index] = a[i - 1];
            i--;j--;
        } else if (cache[i - 1][j] > cache[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    return sub_seq;
}

int main()
{
    int n, m;
    cin >> n >> m;
    int *a = build_sequence(n);
    int *b = build_sequence(m);
    int* sub_seq = lcs(a, n, b, m);
    while (*sub_seq != -1) {
        printf("%d ", *sub_seq++);
    }
    printf("\n");
    return 0;
}
