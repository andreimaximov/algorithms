import java.util.Stack;

public class Solution {
  //
  // Determines if the mutable or immutable algorithm should run by default.
  //
  public static final boolean MUTABLE_ALGO = true;

  public boolean isPalindrome(ListNode head) {
    if (MUTABLE_ALGO) {
      return isPalindromeMutable(head);
    }
    return isPalindromeImmutable(head);
  }

  //
  // Checks if the list is a palindrome. Does not change the underlying list.
  //
  public boolean isPalindromeMutable(ListNode head) {
    ListNode slow = head;
    ListNode fast = head; // Traverse at 2x speed

    // Reverse first half with a stack...
    Stack<Integer> firstHalf = new Stack<>();

    // Traverse till end-of-list such that slow is or is next to the mid-point...
    while (fast != null && fast.next != null) {
      firstHalf.push(slow.val);
      slow = slow.next;
      fast = fast.next.next;
    }

    // Check if the list is odd length...
    boolean isOddLength = (fast != null);

    // Middle element does not matter if this is an odd length list...
    if (isOddLength) {
      slow = slow.next;
    }

    // Now iterate over first half in reverse order and second half in forward
    // order...
    while (!firstHalf.isEmpty()) {
      int value = firstHalf.pop();
      if (value != slow.val) {
        return false;
      }
      slow = slow.next;
    }

    return true;
  }

  //
  // Checks if the list is a palindrome. Changes the underlying list to improve
  // performance.
  //
  public boolean isPalindromeImmutable(ListNode head) {
    ListNode previous = null; // One behind slow node
    ListNode slow = head;
    ListNode fast = head; // Traverses at 2x speed

    // Begin by reversing the first half of the list...
    while (fast != null && fast.next != null) {
      fast = fast.next.next;
      // Set the next node of the current slow node to the previous slow node...
      ListNode nextSlow = slow.next;
      slow.next = previous;
      previous = slow;
      slow = nextSlow;
    }

    // Check if list is odd length...
    boolean isOddLength = (fast == null);

    // Setup two pointers that will traverse middle-out...
    ListNode forward = slow;
    ListNode backwards = previous;

    // Middle element does not matter if this is an odd length list...
    if (isOddLength) {
      forward = forward.next;
    }

    // Check if the two halves are identical...
    while (forward != null || backwards != null) {
      if (forward.val != backwards.val) {
        return false;
      }
      forward.next = forward;
      backwards.next = backwards;
    }

    return true;
  }

  public static void main(String[] args) {
    System.out.println("Please run this solution on LeetCode.");
    System.out.println("https://leetcode.com/problems/palindrome-linked-list/");
  }
}
