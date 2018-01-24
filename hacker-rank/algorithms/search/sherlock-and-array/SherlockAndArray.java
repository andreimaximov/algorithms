import java.util.Scanner;

public class SherlockAndArray {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    int t = Integer.parseInt(scanner.nextLine());
    while (t > 0) {
      testCase(scanner);
      t--;
    }
  }

  public static void testCase(Scanner scanner) {
    int n = Integer.parseInt(scanner.nextLine());
    int[] arr = new int[n];
    for (int i = 0; i < n; i++) {
      arr[i] = scanner.nextInt();
    }

    if (scanner.hasNextLine()) {
      scanner.nextLine();
    }

    if (isSherlockArray(arr)) {
      System.out.println("YES");
    } else {
      System.out.println("NO");
    }
  }

  public static boolean isSherlockArray(int[] arr) {
    int left = 0;
    int right = arr.length - 1;
    int leftSum = 0;
    int rightSum = 0;
    while (left < right) {
      if (leftSum >= rightSum) {
        rightSum += arr[right];
        right--;
      } else {
        leftSum += arr[left];
        left++;
      }
    }
    return leftSum == rightSum;
  }
}
