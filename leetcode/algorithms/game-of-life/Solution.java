public class Solution {
  /**
   * Defines the (x, y) delta distances that can be used to compute each cell's
   * neighbors.
   */
  public static final int[][] NEIGHBORS = {
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {0, 1},
    {1, 1},
    {1, 0},
    {1, -1},
    {0, -1},
  };

  /**
   * Simulate the given board.
   */
  public void gameOfLife(int[][] board) {
    for (int x = 0; x < board.length; x++) {
      for (int y = 0; y < board[x].length; y++) {
        updateCell(board, x, y);
      }
    }
    // Right shift all cells to increment to the next calculated state...
    for (int x = 0; x < board.length; x++) {
      for (int y = 0; y < board[x].length; y++) {
        board[x][y] = board[x][y] >> 1;
      }
    }
  }

  /**
   * Simulates the (x, y) cell applying the next state to the 2nd LSB.
   */
  public void updateCell(int[][] board, int x, int y) {
    int n = numLivingNeighbors(board, x, y);
    if (isAlive(board, x, y)) {
      if (n < 2 || n > 3) {
        setAlive(board, x, y, false);
      } else {
        setAlive(board, x, y, true);
      }
    } else if (n == 3) {
      setAlive(board, x, y, true);
    }
  }

  /**
   * Sets the next state of cell (x, y) (2nd LSB) to the alive boolean.
   */
  public void setAlive(int[][] board, int x, int y, boolean alive) {
    if (!alive) {
      return;
    }
    // Set the 2nd LSB to set alive in the next iteration...
    board[x][y] |= 2;
  }

  /**
   * Counts the number of living neighbors cell (x, y) has.
   */
  public int numLivingNeighbors(int[][] board, int x, int y) {
    int count = 0;
    for (int[] delta : NEIGHBORS) {
      if (isAlive(board, x + delta[0], y + delta[1])) {
        count++;
      }
    }
    return count;
  }

  /**
   * Checks if cell (x, y) is alive. Out of bounds cells are considered dead.
   */
  public boolean isAlive(int[][] board, int x, int y) {
    if (x < 0 || y < 0 || x >= board.length || y >= board[x].length) {
      return false;
    }
    // Check if the LSB is set...
    return (board[x][y] & 1) == 1;
  }

  public static void main(String[] args) {
    System.out.println("Please run this solution on LeetCode.");
    System.out.println("https://leetcode.com/problems/game-of-life/");
  }
}
