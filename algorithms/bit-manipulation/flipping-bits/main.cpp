#include <iostream>

using namespace std;

int main() {
    unsigned int T, i;
    scanf("%u", &T);
    while (T > 0) {
        scanf("%u", &i);
        printf("%u\n", ~i);
        T--;
    }
    return 0;
}
