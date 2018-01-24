import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.math.BigInteger;

public class Solution {
  public static void main(String[] args) {
    BufferedReader bi = new BufferedReader(new InputStreamReader(System.in));
    String[] tokens = null;
    try {
      tokens = bi.readLine().split("\\s");
    } catch (IOException e) {
      System.err.println(e);
      System.exit(1);
    }
    BigInteger b = new BigInteger(tokens[0]);
    BigInteger a = new BigInteger(tokens[1]);
    int n = Integer.parseInt(tokens[2]) - 2;

    BigInteger tmp = null;
    while (n > 0) {
      tmp = a;
      a = a.multiply(a).add(b);
      b = tmp;
      --n;
    }

    System.out.println(a);
  }
}
