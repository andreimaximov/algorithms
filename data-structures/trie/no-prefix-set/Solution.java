import java.util.Scanner;

class TrieNode {
  public boolean eos;

  public TrieNode[] children;

  public static int RANGE = 'j' - 'a' + 1;

  public TrieNode() {
    this.eos = true;
    this.children = new TrieNode[RANGE];
  }
}

class Trie {
  private TrieNode root;

  public Trie() {
    this.root = new TrieNode();
  }

  public boolean add(String word) {
    TrieNode node = root;
    int index = 0;
    while (index < word.length()) {
      node.eos = false;
      char c = word.charAt(index);
      int i = c - 'a';
      if (node.children[i] == null) {
        node.children[i] = new TrieNode();
      } else if (node.children[i].eos || index == word.length() - 1) {
        return false;
      }
      node = node.children[i];
      index++;
    }
    return true;
  }
}

public class Solution {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);

    int N = scanner.nextInt();
    scanner.nextLine();

    Trie trie = new Trie();

    for (int i = 0; i < N; i++) {
      String word = scanner.nextLine();
      if (!trie.add(word)) {
        System.out.println("BAD SET");
        System.out.println(word);
        return;
      }
    }

    System.out.println("GOOD SET");
  }
}
