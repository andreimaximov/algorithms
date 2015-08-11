#include <iostream>

using namespace std;

int* read_message(int length) {
    int* message = new int[length];
    for (int i = 0; i < length; i++) {
        scanf("%1d", &message[i]);
    }
    return message;
}

int* decode(int* message, int length, int N, int K) {
    int last_k_xor = message[0];
    int* decoded = new int[N];
    decoded[0] = message[0];
    for (int i = 1; i < N; i++) {
        if (i >= K) {
            last_k_xor = last_k_xor ^ decoded[i - K];
        }
        decoded[i] = last_k_xor ^ message[i];
        last_k_xor = last_k_xor ^ decoded[i];
    }
    return decoded;
}

int main() {
    int N, K;
    scanf("%d", &N);
    scanf("%d", &K);
    int length = N + K - 1;
    int* S = read_message(length);
    int* decoded = decode(S, length, N, K);
    for (int i = 0; i < N; i++) {
        printf("%d", decoded[i]);
    }
    printf("\n");
    return 0;
}
