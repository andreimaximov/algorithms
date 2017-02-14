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
// Returns the length of the longest common prefix of sequences [aBegin, aEnd)
// and [bBegin, bEnd).
//
template<typename Iterator>
size_t common_prefix(Iterator aBegin, Iterator aEnd,
                     Iterator bBegin, Iterator bEnd) {
  size_t length = 0;

  while (aBegin != aEnd && bBegin != bEnd && *aBegin == *bBegin) {
    aBegin++;
    bBegin++;
    length++;
  }

  return length;
}

//
// Generic iterator based Z-Algorithm. Returns a table Z where each Z[i]
// represents the longest string S[i...i + Z[i] - 1] that is also a prefix of
// S[0...].
//
// The following article is an excellent explanation behind the logic of this
// algorithm: https://ivanyu.me/blog/2013/10/15/z-algorithm/
//
template<typename Iterator>
std::vector<int> z_search(Iterator begin, Iterator end) {
  // Setup table and base case.
  std::vector<int> Z(std::distance(begin, end));
  Z[0] = Z.size();

  // Setup iterator and track the index/distance we are from the start of the
  // sequence.
  Iterator it = std::next(begin);
  int i = 1;

  // Setup z-box such that S[l...r] = S[0...r - l] at all times.
  int l = 0;
  int r = 0;

  while (it != end) {
    if (i > r) {
      // If the current index is outside of the z-box then compute Z[i] using
      // standard algorithm.
      Z[i] = common_prefix(begin, end, it, end);

      // Update z-box to enclose [i, i + Z[i]) which is the longest prefix of
      // the sequence starting at i.
      l = i;
      r = i + Z[i] - 1;
    } else {
      // p is the index i maps to in the prefix of the sequence.
      int p = i - l;

      // Length of right side of z-box including current index.
      int k = r - i + 1;

      // See article for explanation.
      if (Z[p] < k) {
        Z[i] = Z[p];
      } else {
        Iterator left = offset(begin, k);
        Iterator right = offset(it, k);
        Z[i] = k + common_prefix(left, end, right, end);

        // Update z-box
        l = i;
        r = i + Z[i] - 1;
      }
    }

    it++;
    i++;
  }

  return Z;
}

//
// Returns indexes in T where full occurences of P begin.
//
std::vector<size_t> find(const std::string& P,
                         const std::string& T,
                         char separator = '#') {
  std::string S = P + std::string(1, separator) + T;
  std::vector<int> Z = z_search(S.begin(), S.end());
  std::vector<size_t> index;

  for (size_t i = P.size() + 1; i < Z.size(); i++) {
    if (Z[i] == static_cast<int>(P.size())) {
      index.push_back(i - P.size() - 1);
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

