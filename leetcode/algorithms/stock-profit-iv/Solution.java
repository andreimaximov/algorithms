import java.util.Arrays;
import java.util.Random;

public class Solution {
  public int maxProfit(int k, int[] prices) {
    int n = prices.length;

    // Can't make any profitable transactions.
    if (k == 0 || n < 2) {
        return 0;
    }

    //
    // It is not possible to make more than n - 1 non-overlapping transactions
    // so if k >= n - 1 we could pretend we had unlimited transactions. (Note:
    // we can still buy and sell same day as long as sell is before buy)
    //
    // However, having at least n / 2 transactions is also sufficient because
    // we do not actually need to be able to sell and buy on the same day -
    // There is no purpose or gain from such a transaction. One might as well
    // hold their position if it will be beneficial to sell on a later day.
    //
    if (k >= prices.length/2) {
        return maxProfit(prices);
    }

    //
    // Use the following recurence relation to solve the problem.
    //
    // dp[i][j] = Max profit in interval [0, j] using at most i transactions.
    //
    // Mathematically...
    //
    // dp[i][j] = max(dp[i][j - 1], max({dp[i - 1][m] + prices[j] - prices[m]} for 0 <= m < j))
    //
    // Which can be simplified to...
    //
    // dp[i][j] = max(dp[i][j - 1], prices[j] + max({dp[i - 1][m] - prices[m]}))
    //
    int[][] dp = new int[k + 1][prices.length];
    for (int i = 1; i <= k; i++) {
        int splitMax = dp[i - 1][0] - prices[0]; // Represents dp[i - 1][m] - prices[m] term
        for (int j = 1; j < prices.length; j++) {
            dp[i][j] = Math.max(dp[i][j - 1], prices[j] + splitMax);
            splitMax = Math.max(splitMax, dp[i - 1][j] - prices[j]);
        }
    }

    return dp[k][prices.length - 1];
  }

  //
  // Calculates the maximum trading profit over the given price history using
  // an unlimited number of non-overlapping transactions. Transactions consists
  // of buying and selling exactly one unit of stock.
  //
  public int maxProfit(int[] prices) {
    int profit = 0;
    for (int i = 1; i < prices.length; i++) {
      if (prices[i] > prices[i - 1]) {
        profit += prices[i] - prices[i - 1];
      }
    }
    return profit;
  }

  public static void main(String[] args) {
    System.out.println("Please run this solution on LeetCode.");
    System.out.println("https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/");
  }
}
