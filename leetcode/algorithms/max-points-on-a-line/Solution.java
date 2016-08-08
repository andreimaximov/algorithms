import java.util.HashMap;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class Solution {
  //
  // EpsionCounter can be used to efficiently count numbers that are within
  // a specified floating-point epison of each other.
  //
  public static class EpsilonCounter<T extends Number> {
    private Map<Double, List<T>> buckets = new HashMap<>();

    //
    // Numbers with a difference less than or equal to epsilon are "equal".
    //
    private double epsilon;

    public EpsilonCounter(double epsilon) {
      this.epsilon = epsilon;
    }

    //
    // Adds a number to the set.
    //
    public void add(T number) {
      double key = getKey(number);
      List<T> bucket = buckets.get(key);

      // Create a new bucket if one does not already exist.
      if (bucket == null) {
        bucket = new ArrayList<>();
        buckets.put(key, bucket);
      }

      // Add number to correct bucket.
      bucket.add(number);
    }

    //
    // Counts the numbers in the current set that are within the interval
    // [number - epsilon, number + epsilon].
    //
    public long count(T number) {
      double key = getKey(number);
      double base = number.doubleValue();
      List<T> here = buckets.get(key); // All candidates are in desired interval
      List<T> upper = buckets.get(key + epsilon); // Some candidates might be too large
      List<T> lower = buckets.get(key - epsilon); // Some candidates might be too small
      return here.size() + countWithinEpsilon(upper, base) + countWithinEpsilon(lower, base);
    }

    //
    // Clears all numbers from the set.
    //
    public void clear() {
      buckets.clear();
    }

    //
    // Calcultes the bucket this number belongs to. All numbers in this bucket
    // should be within the specified epsilon value.
    //
    private double getKey(T number) {
      int factor = (int) (number.doubleValue() / epsilon);
      return factor * epsilon;
    }

    //
    // Counts the numbers in the collection that are within the interval
    // [number - epsilon, number + epsilon].
    //
    private long countWithinEpsilon(List<T> collection, double number) {
      if (collection == null) {
        return 0;
      }
      return collection
          .stream()
          .filter(candidate -> {
            return Math.abs(candidate.doubleValue() - number) <= epsilon;
          })
          .count();
    }
  }

  //
  // Default epsilon value for this problem. See EpsilonCounter for details.
  //
  public static final double EPSILON = 0.0001;

  //
  // Returns the maximum number of points in the list that lie on the same
  // straight line.
  //
  public int maxPoints(Point[] points) {
    // Base case.
    if (points.length < 2) {
      return points.length;
    }

    // Efficiently roughly "equal" floating-point slope values.
    EpsilonCounter<Double> slopes = new EpsilonCounter<>(EPSILON);
    int max = 0;

    for (int i = 0; i < points.length; i++) {
      // The source point from which we are casting lines to all other points.
      Point from = points[i];
      int duplicates = 1; // Track points identical to the source.
      int vertical = 0; // Track points that are directly above or below the source.
      int candidate = 0; // Max number of points on a line starting at this source.
      slopes.clear();

      for (int j = i + 1; j < points.length; j++) {
        // The target point to which we are casting a line.
        Point to = points[j];

        // Check for vertically aligned or duplicate points.
        if (from.x == to.x) {
          if (from.y == to.y) {
            duplicates++;
          } else {
            vertical++;
          }
        } else {
          // Calculate how many lines with "equal" slopes are being cast from
          // the current source point.
          double slope = getSlope(from, to);
          slopes.add(slope);
          candidate = Math.max(candidate, (int) slopes.count(slope));
        }
      }

      // Check if there are more duplicates than other points on the same line
      // and account for duplicates.
      candidate = Math.max(candidate, vertical) + duplicates;
      // Update max points on line from any source point.
      max = Math.max(max, candidate);
    }

    return max;
  }

  //
  // Returns the slope between two points. Does not perform checks for points
  // that form a vertical line.
  //
  public double getSlope(Point a, Point b) {
    if (a.y == b.y) {
      return 0.0;
    }
    return (double) (a.y - b.y) / (a.x - b.x);
  }

  public static void main(String[] args) {
    System.out.println("Please run this solution on LeetCode.");
    System.out.println("https://leetcode.com/problems/max-points-on-a-line/");
  }
}
