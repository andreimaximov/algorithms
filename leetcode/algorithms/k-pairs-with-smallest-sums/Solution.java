import java.util.ArrayList;
import java.util.List;
import java.util.PriorityQueue;

public class Solution {
  private static class Pair implements Comparable<Pair> {
    private int x;

    private int y;

    private Integer value;

    public Pair(int x, int y, int value) {
      this.x = x;
      this.y = y;
      this.value = value;
    }

    //
    // Compares the pairs according to the internal values.
    //
    public int compareTo(Pair other) {
      return value.compareTo(other.value);
    }

    //
    // Creates a pair representing {a[x], b[y]}.
    //
    public static Pair toPair(int[] a, int x, int[] b, int y) {
      return new Pair(x, y, a[x] + b[y]);
    }
  }

  //
  // {x, y} offsets to get the next smallest pair.
  //
  private static final int[][] NEXT_PAIRS = {{0, 1}, {1, 0}};

  public List<int[]> kSmallestPairs(int[] a, int[] b, int k) {
    ArrayList<int[]> pairs = new ArrayList<int[]>();

    // Return early if no pairs are desired...
    if (k <= 0 || a.length == 0 || b.length == 0) {
      return pairs;
    }

    // Generate a matrix of all a.length x b.length pairs to keep track of the
    // ones we have visited...
    boolean[][] visited = new boolean[a.length][b.length];

    // Begin by adding the smallest pair...
    PriorityQueue<Pair> queue = new PriorityQueue<>();
    queue.add(Pair.toPair(a, 0, b, 0));

    // Continue until we run out or do need need any more pairs...
    while (k-- > 0 && !queue.isEmpty()) {
      Pair pair = queue.poll();
      pairs.add(toArray(a[pair.x], b[pair.y]));

      // Add next pair candidates to queue...
      for (int[] offset : NEXT_PAIRS) {
        int x = pair.x + offset[0];
        int y = pair.y + offset[1];
        if (x < a.length && y < b.length && !visited[x][y]) {
          queue.add(Pair.toPair(a, x, b, y));
          visited[x][y] = true;
        }
      }
    }

    return pairs;
  }

  //
  // Wraps x and y to return an array {x, y}.
  //
  public static int[] toArray(int x, int y) {
    return new int[] {x, y};
  }

  public static void main(String[] args) {
    System.out.println("Please run this solution on LeetCode.");
    System.out.println("https://leetcode.com/problems/find-k-pairs-with-smallest-sums/");
  }
}
