#include <iostream>
#include <stack>

using namespace std;

const int delta_x[] = {-1, 0, 1, 1, 1, 0, -1, -1};
const int delta_y[] = {-1, -1, -1, 0, 1, 1, 1, 0};

int** build_grid(int m, int n) {
    int** grid = new int*[m];
    for (int i = 0; i < m; i++) {
        grid[i] = new int[n];
        for (int k = 0; k < n; k++) {
            scanf("%d", &grid[i][k]);
        }
    }
    return grid;
}

int flood_fill(int** grid, int m, int n, int r, int c) {
    int size = 1, x, y;
    grid[r][c] = 0;
    for (int i = 0; i < 8; i++) {
        x = c + delta_x[i];
        y = r + delta_y[i];
        // Out of bounds check.
        if (x < 0 || x >= n || y < 0 || y >= m) {
            continue;
        }
        // Out of region or already visited.
        if (grid[y][x] == 0) {
            continue;
        }
        size += flood_fill(grid, m, n, y, x);
    }
    return size;
}

int max_region(int** grid, int m, int n) {
    int largest_region = 0;
    for (int i = 0; i < m; i++) {
        for (int k = 0; k < n; k++) {
            // Skip out of region or visited cells.
            if (grid[i][k] == 0) {
                continue;
            }
            largest_region = max(largest_region, flood_fill(grid, m, n, i, k));
        }
    }
    return largest_region;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    int** grid = build_grid(m, n);
    printf("%d\n", max_region(grid, m, n));
    return 0;
}
