import java.util.Scanner;
import java.util.TreeSet;

public class Solution {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    int t = Integer.parseInt(scanner.nextLine());

    for (int i = 0; i < t; i++) {
      testCase(scanner);
    }
  }

  public static void testCase(Scanner scanner) {
    // Read in N and M.
    int n = scanner.nextInt();
    long m = scanner.nextLong();
    scanner.nextLine();

    // Keep track of the current and max prefix.
    long max = 0;
    long prefix = 0;

    // Use a tree to efficiently query previous prefixes
    TreeSet<Long> treeSet = new TreeSet<Long>();
    treeSet.add(prefix);

    for (int i = 0; i < n; i++) {
      // Read in next element.
      long e = scanner.nextLong();

      // Calculate the mod-sum of the sub-array 0 to i.
      prefix = (prefix + e) % m;
      max = Math.max(max, prefix);

      // Check for the lowest prefix greater than this one.
      Long start = treeSet.higher(prefix);
      if (start != null) {
          max = Math.max(max, (prefix - start + m) % m);
      }

      // Update prefix tree.
      treeSet.add(prefix);
    }

    if (scanner.hasNextLine()) {
      scanner.nextLine();
    }

    System.out.println(max);
  }
}
