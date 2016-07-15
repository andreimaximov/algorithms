public class Solution {
  //
  // Checks if a is a rotation of b.
  //
  public static boolean isRotation(String a, String b) {
    if (a.length() != b.length() || a.length() == 0) {
      return false;
    }
    a = a + a;
    return a.contains(b);
  }

  public static void main(String[] args) {
    assert isRotation("dogs", "gsdo");
    assert !isRotation("dogs", "dog");
    assert !isRotation("dodogo", "dogogo");
  }
}
