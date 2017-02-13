#include <vector>
#include <iterator>
#include <cassert>
#include <iostream>

//
// Copy wrapper around std::advance
//
template<typename Iterator, typename Distance>
Iterator offset(Iterator it, Distance dist) {
  std::advance(it, dist);
  return it;
}

//
// Generic KMP iterator based algorithm. Returns a table F where each F[i]
// represents the longest proper suffix of S[0...i] that is also a prefix of
// S[0...i] where S = [begin, end).
//
template<typename Iterator>
std::vector<int> kmp(Iterator begin, Iterator end) {
  // Setup table and base case.
  std::vector<int> F(std::distance(begin, end));
  F[0] = 0;

  // Setup iterator and track the index/distance we are from start of
  // sequence.
  Iterator it = next(begin);
  int i = 1;

  while (it != end) {
    int j = F[i - 1];
    Iterator jIt = offset(begin, j);

    while (j > 0 && *jIt != *it) {
      j = F[j - 1];
      jIt = offset(begin, j);
    }

    if (*jIt == *it) {
      j++;
    }

    F[i] = j;

    it++;
    i++;
  }

  return F;
}

//
// Returns indexes in T where full occurences of P begin.
//
std::vector<size_t> find(const std::string& P,
                         const std::string& T,
                         char separator = '#') {
  std::string S = P + std::string(1, separator) + T;
  std::vector<int> F = kmp(S.begin(), S.end());
  std::vector<size_t> index;

  for (size_t i = 0; i < F.size(); i++) {
    if (F[i] == static_cast<int>(P.size())) {
      index.push_back(i - 2 * P.size());
    }
  }

  return index;
}

int main() {
  assert(find("a", "a") == std::vector<size_t>({0}));
  assert(find("sda", "sadasda") == std::vector<size_t>({4}));
  assert(find("rishi", "rishrisrishirishirishrishiririshi") ==
      std::vector<size_t>({7, 12, 21, 28}));
  assert(find("aa", "aaaa") == std::vector<size_t>({0, 1, 2}));
  assert(find("AABA", "AABAACAADAABAABA") == std::vector<size_t>({0, 9, 12}));
  assert(find("TEST", "THIS IS A TEST TEXT") == std::vector<size_t>({10}));

  std::cout << "Tests pass!" << std::endl;

  return 0;
}

