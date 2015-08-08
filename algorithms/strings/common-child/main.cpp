#include <iostream>

using namespace std;

int lcs(string &a, string &b) {
    int m = a.length() + 1;
    int n = b.length() + 1;
    int** cache = new int*[m];
    for (int i = 0; i < m; i++) {
        cache[i] = new int[n];
        for (int j = 0; j < n; j++) {
            if (i == 0 || j == 0) {
                cache[i][j] = 0;
            } else if (a.at(i - 1) == b.at(j - 1)) {
                cache[i][j] = cache[i - 1][j - 1] + 1;
            } else {
                cache[i][j] = max(cache[i][j - 1],  cache[i - 1][j]);
            }
        }
    }
    return cache[a.length()][b.length()];
}

int main() {
    string a, b;
    cin >> a;
    cin >> b;
    printf("%d\n", lcs(a, b));
    return 0;
}
