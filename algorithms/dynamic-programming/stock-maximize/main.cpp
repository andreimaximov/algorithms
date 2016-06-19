#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

//
// Calculate the maximum trading profit possible given a price history.
//
uint64_t maxProfit(const std::vector<uint32_t>& prices) {
  // No profit possible with less than 2 trading days...
  if (prices.size() < 2) {
    return 0;
  }
  uint64_t profit = 0;
  // Highest price in first i + 1 prices...
  uint32_t high = prices[prices.size() - 1];
  // Go through prices in reverse...
  for (int i = prices.size() - 2; i >= 0; i--) {
    if (prices[i] > high) {
      high = prices[i];
    }
    // The potential profit from a purchase today...
    profit += high - prices[i];
  }
  return profit;
}

//
// Read N stock prices into a vector of size N.
//
std::vector<uint32_t> loadPrices(std::istream& in, size_t N) { // NOLINT
  std::vector<uint32_t> prices;
  std::copy_n(std::istream_iterator<uint32_t>(std::cin),
              N,
              std::back_inserter(prices));
  return prices;
}

int main() {
  size_t T, N;
  std::cin >> T;
  while (T--) {
    std::cin >> N;
    std::vector<uint32_t> prices = loadPrices(std::cin, N);
    std::cout << maxProfit(prices) << std::endl;
  }
  return 0;
}
