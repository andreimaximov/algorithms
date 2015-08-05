#include <iostream>
#include <vector>

using namespace std;

const int MIN = -2000;
const int MAX = 2000;
const int ORIGIN = 2001;
const int SIZE = MAX - MIN + 3;

struct Position {
    long long left_sum, right_sum, self_sum, left_count, right_count, self_count;
};

Position* build_array(int size, int N) {
    Position* positions = new Position[size];
    while (size > 0) {
        positions[--size].self_count = 0;
    }
    int current;
    while (N > 0) {
        scanf("%d", &current);
        positions[current + ORIGIN].self_count++;
        N--;
    }
    return positions;
}

void calculate_from_left(Position* positions, int size) {
    positions[0].left_count = 0;
    positions[0].left_sum = 0;
    for (int i = 1; i < size; i++) {
        positions[i].left_count = positions[i - 1].left_count + positions[i - 1].self_count;
        positions[i].left_sum = positions[i - 1].left_sum + positions[i - 1].left_count + positions[i - 1].self_count;
    }
}

void calculate_from_right(Position* positions, int size) {
    positions[size - 1].right_count = 0;
    positions[size - 1].right_sum = 0;
    for (int i = size - 2; i >= 0; i--) {
        positions[i].right_count = positions[i + 1].right_count + positions[i + 1].self_count;
        positions[i].right_sum = positions[i + 1].right_sum + positions[i + 1].right_count + positions[i + 1].self_count;
    }
}

void calculate_positions(Position* positions, int size) {
    calculate_from_left(positions, size);
    calculate_from_right(positions, size);
    for (int i = 0; i < size; i++) {
        positions[i].self_sum = positions[i].left_sum + positions[i].right_sum;
    }
}

long long query(Position* positions, int size, long long &index, int q) {
    index -= q;
    if (index < 0) {
        return positions[0].right_sum + positions[0].right_count * (-index);
    } else if (index > size - 1) {
        return positions[size-1].left_sum + positions[size-1].left_count * (index - size + 1);
    }
    return positions[index].self_sum;
}

int main() {
    int N, Q, q;
    scanf("%d", &N);
    Position* positions = build_array(SIZE, N);
    calculate_positions(positions, SIZE);
    scanf("%d", &Q);
    long long index = ORIGIN;
    while (Q > 0) {
        scanf("%d", &q);
        printf("%lli\n", query(positions, SIZE, index, q));
        Q--;
    }
    return 0;
}
