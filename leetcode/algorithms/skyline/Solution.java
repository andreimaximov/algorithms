import java.util.Arrays;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.PriorityQueue;

//
// See inline comments for algorithm explanation. More information can be found
// at http://buttercola.blogspot.com/2015/08/leetcode-skyline-problem.html.
//
public class Solution {
  private static final int[][] TEST_BUILDINGS = {
    {2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8}
  };

  private static final List<int[]> TEST_SKYLINE = Arrays.asList(point(2, 10), point(3, 15),
    point(7, 12), point(12, 0), point(15, 10), point(20, 8), point(24, 0)
  );

  //
  // Represents the vertical edge of a building.
  //
  private static class Edge {
    int x;

    int height;

    //
    // True indicates the edge is the left side of a building.
    //
    boolean isStart;

    public Edge(int x, int height, boolean isStart) {
      this.x = x;
      this.height = height;
      this.isStart = isStart;
    }
  }

  public static class EdgeSkylineComparator implements Comparator<Edge> {
    public int compare(Edge lhs, Edge rhs) {
      if (lhs.x != rhs.x) {
        return lhs.x - rhs.x;
      } else if (lhs.isStart && rhs.isStart) {

        // Edge with greater height has higher priority if both edges are
        // starting edges because edge with lower height gets hidden in the
        // skyline.
        return rhs.height - lhs.height;
      } else if (!lhs.isStart && !rhs.isStart) {

        // Edge with lower height has higher priority if both edges are ending
        // edges because we need to make sure the highest edge in a series of
        // end edges on the same vertical gets processed last. We would still
        // get an accurate skyline without this check, but could end up with
        // redundant points on the same vertical line of the skyline. See case
        // 1.1 and 1.2 of {@link getSkyline} for details.
        return lhs.height - rhs.height;
      } else {

        // Process building start edges first This is important for avoiding
        // redundant points on the same vertical. Say we encounter buildings
        // {0, 1, 1}, {1, 2, 2}. The height of the skyline is thus {1, 2} for
        // one horizontal unit each. We need to make sure we process the start
        // edge of the second building first to prevent a -1 height change
        // before a +2 recovery. This should just appear a single +1 height
        // increase operation.
        return lhs.isStart ? -1 : 1;
      }
    }
  }

  public List<int[]> getSkyline(int[][] buildings) {
    // Transform each building into a sorted list of start and end edges.
    List<Edge> edges = new ArrayList<>(buildings.length * 2);
    for (int[] building : buildings) {
      edges.add(new Edge(building[0], building[2], true));
      edges.add(new Edge(building[1], building[2], false));
    }
    Collections.sort(edges, new EdgeSkylineComparator());

    // Build the skyline.
    List<int[]> skyline = new ArrayList<>();
    PriorityQueue<Integer> heights = new PriorityQueue<>(Math.max(1, edges.size() / 4),
        Collections.reverseOrder());

    //
    // There are two main cases to process an edge:
    //
    // 1. We have reached the edge of a new building.
    //
    // 2. Passing a previously encountered building.
    //
    for (Edge edge : edges) {
      if (edge.isStart) {
        // Add this critical point to skyline if there are no buildings that
        // have started but not finished yet that are taller.
        if (heights.isEmpty() || heights.peek() < edge.height) {
          skyline.add(point(edge.x, edge.height));
        }
        heights.offer(edge.height);
      } else {
        heights.remove(edge.height);

        // We can add a "lower" critical point that decreases the height of the
        // skyline in two cases:
        //
        // 1. We have passed all previous buildings so the skyline drops to
        //    level 0.
        //
        // 2. The tallest building left is not as tall as the building we just
        //    passed with the current edge. The skyline drops to the height of
        //    this next tallest building. End edges on the same vertical should
        //    be processed in order of tallest edge last. This is to ensure the
        //    final edge triggers a single skyline height drop instead of a
        //    series of incremental drops.
        if (heights.isEmpty()) {
          // Case 1
          skyline.add(point(edge.x, 0));
        } else if (heights.peek() < edge.height) {
          // Case 2
          skyline.add(point(edge.x, heights.peek()));
        }
      }
    }

    return skyline;
  }

  //
  // Point factory helper.
  //
  public static int[] point(int x, int y) {
    return new int[] {x, y};
  }

  public static void main(String[] args) {
    Solution solution = new Solution();
    List<int[]> skyline = solution.getSkyline(TEST_BUILDINGS);
    assert Arrays.deepEquals(TEST_SKYLINE.toArray(), skyline.toArray());

    System.out.println("Tests pass!");
    System.out.println("Please run this solution on LeetCode.");
    System.out.println("https://leetcode.com/problems/set-matrix-zeroes/");
  }
}
