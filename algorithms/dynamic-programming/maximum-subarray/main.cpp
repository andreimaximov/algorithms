#include <iostream>
#include <limits.h>

using namespace std;

int* build_array(int N) {
    int* array = new int[N];
    for (int i = 0; i < N; i++) {
        cin >> array[i];
    }
    cin.ignore();
    return array;
}

int kadane(int* array, int N) {
    int max_here = 0, max_previous = INT_MIN, max_all = INT_MIN, current = 0;
    for (int i = 0; i < N; i++) {
        current = array[i];
        max_here = max(max_previous, max_here + current);
        max_all = max(max_all, max_here);
        max_previous = min(0, max_here);
    }
    return max_all;
}

int max_element_sum(int* array, int N) {
    int max_sum = INT_MIN, current = 0;
    for (int i = 0; i < N; i++) {
        current = array[i];
        if (max_sum < 0 && current < 0) {
            max_sum = max(max_sum, current);
            continue;
        }
        max_sum = max(0, max_sum);
        max_sum += max(0, current);
    }
    return max_sum;
}

void test_case()
{
    int N = 0;
    cin >> N;
    cin.ignore();
    int* array = build_array(N);
    int max_cont = kadane(array, N);
    int max_non_cont = max_element_sum(array, N);
    delete [] array;
    cout << max_cont << " " << max_non_cont << endl;
}

int main()
{
    int T = 0;
    cin >> T;
    cin.ignore();
    while (T > 0) {
        test_case();
        T--;
    }
    return 0;
}
