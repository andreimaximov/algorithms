#include <iostream>
#include <climits>

using namespace std;

const int range = 101;

void flush_line()
{
    cin.clear();
    cin.ignore(INT_MAX, '\n');
}

void next(int *freq_map, int *num_map, int n, bool add, int &min)
{
    int k, m;
    cin >> k;
    while (k > 0) {
        cin >> m;
        int mod = m % n;
        if (add) {
            ++freq_map[mod];
        } else {
            --freq_map[mod];
        }
        num_map[mod] = m;
        if (min == -1 || m < num_map[min]) {
            min = mod;
        }
        --k;
    }
    flush_line();
}

int main()
{
    int freq_map[range] = {0};
    int num_map[range] = {0};
    int min = -1;
    next(freq_map, num_map, range, true, min);
    next(freq_map, num_map, range, false, min);
    int index;
    for (int i = 0; i < range; ++i) {
        index = (i + min) % (range - 1);
        if (freq_map[index] == 0) {
            continue;
        }
        cout << num_map[index] << ' ';
    }
    cout << endl;
}
