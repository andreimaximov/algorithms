#include <iostream>
#include <vector>
#include <iterator>

std::vector<bool> decode(const std::vector<bool>& message, int N, int K) {
  bool last_k_xor = message[0];
  std::vector<bool> decoded(N, 0);
  decoded[0] = message[0];
  for (int i = 1; i < N; ++i) {
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
  std::cin >> N >> K;

  int length = N + K - 1;
  std::vector<bool> message(length);
  char c;
  for (size_t i = 0; i < message.size(); ++i) {
    std::cin >> c;
    message[i] = c - '0';
  }

  std::vector<bool> decoded = decode(message, N, K);
  std::ostream_iterator<bool> out(std::cout);
  std::copy(decoded.begin(), decoded.end(), out);
  return 0;
}
