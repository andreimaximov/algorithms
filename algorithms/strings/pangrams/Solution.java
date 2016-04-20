import java.io.IOException;

public class Solution {
  public static void main(String[] args) throws IOException {
    // Tracks xor between alphabet and string characters
    int xor = 0;

    // Each "on" bit represents an occurence of a character
    int alphas = 0;

    // xor the alphabet characters together
    for (int i = 0; i < 26; i++) {
      xor ^= i;
    }

    int c;
    while ((c = System.in.read()) != -1) {
      c = Character.toLowerCase(c);
      if (c < 'a' || c > 'z') continue;
      c -= 'a';
      if (((alphas >> c) & 1) ==  1) continue;
      xor ^= c;
      alphas |= 1 << c;
    }

    if (xor == 0) {
      System.out.println("pangram");
    } else {
      System.out.println("not pangram");
    }
  }
}
