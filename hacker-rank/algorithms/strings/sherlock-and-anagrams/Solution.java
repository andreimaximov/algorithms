import java.util.Arrays;
import java.util.HashMap;
import java.util.Scanner;

public class Solution {
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);

    int T = in.nextInt();
    in.nextLine();

    while (T > 0) {
      testCase(in);
      T--;
    }
  }

  public static void testCase(Scanner in) {
    String str = in.nextLine();

    HashMap<String, Integer> map = new HashMap<String, Integer>();

    // Count the number of substrings that form each anagram.
    for (int i = 0; i < str.length(); i++) {
      for (int n = i; n < str.length(); n++) {
        char[] substr = str.substring(i, n + 1).toCharArray();
        Arrays.sort(substr);
        String key = new String(substr);
        if (!map.containsKey(key)) {
          map.put(key, 1);
        } else {
          map.put(key, map.get(key) + 1);
        }
      }
    }

    // Count the number of substring pairs that form each anagram.
    int count = 0;
    for (int subs : map.values()) {
      count += subs * (subs - 1) * 0.5;
    }

    System.out.println(count);
  }
}
