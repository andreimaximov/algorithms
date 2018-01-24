import java.util.Scanner;

public class Solution {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);

    int n = Integer.parseInt(scanner.nextLine());
    int[] array = new int[n];
    for (int i = 0; i < n; ++i) {
      array[i] = scanner.nextInt();
    }

    quicksort(array, 0, array.length - 1);
  }

  public static void quicksort(int[] array, int lo, int hi) {
    if (lo >= hi) {
      return;
    }

    int partition = partition(array, lo, hi, hi);
    quicksort(array, lo, partition - 1);
    quicksort(array, partition + 1, hi);
  }

  public static int partition(int[] array, int lo, int hi, int pivot) {
    int store = lo;
    for (int i = lo; i < hi; ++i) {
      if (array[i] < array[pivot]) {
        swap(array, i, store);
        ++store;
      }
    }
    swap(array, pivot, store);
    printArray(array);

    return store;
  }

  public static void swap(int[] array, int a, int b) {
    int tmp = array[a];
    array[a] = array[b];
    array[b] = tmp;
  }

  public static void printArray(int[] array) {
    for (int i = 0; i < array.length; ++i) {
      if (i > 0) {
        System.out.print(" ");
      }
      System.out.print(array[i]);
    }
    System.out.println();
  }
}
