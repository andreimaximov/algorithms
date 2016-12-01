import java.util.TreeSet;
import java.util.HashMap;

public class LFUCache {
  private class Entry implements Comparable<Entry> {
    public int key;

    public int value;

    public int usage;

    public int time;

    public Entry(int key, int value) {
      this.key = key;
      this.value = value;
      this.usage = 0;
      this.time = LFUCache.this.time++;
    }

    //
    // Compares entries by usage and timestamp. To modify an entry, you can
    // remove it from the tree set, update it, and add it back. This will work
    // because the usage and timestamp information will uniquely identify the
    // entry if left untouched.
    //
    public int compareTo(Entry other) {
      if (usage < other.usage) {
        return -1;
      } else if (usage == other.usage) {
        return time - other.time;
      }
      return 1;
    }
  }

  private TreeSet<Entry> ordering = new TreeSet<>();

  private HashMap<Integer, Entry> index = new HashMap<>();

  private int capacity;

  private int time;

  public LFUCache(int capacity) {
    this.capacity = Math.max(capacity, 0);
  }

  public int get(int key) {
    if (!index.containsKey(key)) {
      return -1;
    }
    Entry entry = index.get(key);
    ping(entry);
    return entry.value;
  }

  public void set(int key, int value) {
    // No point in continuing...
    if (capacity == 0) {
      return;
    }

    if (index.containsKey(key)) {
      // Update the entry.
      Entry entry = index.get(key);
      entry.value = value;
      ping(entry);
    } else {
      if (index.size() == capacity) {
        // Remove the LFU entry if are at a capacity limit.
        Entry entry = ordering.first();
        ordering.remove(entry);
        index.remove(entry.key);
      }
      // Add the entry for this key.
      index.put(key, new Entry(key, value));
      ordering.add(index.get(key));
    }
  }

  //
  // Updates the timestamp and usage information for the entry. Updates the
  // ordering of all the entries.
  //
  private void ping(Entry entry) {
    ordering.remove(entry);
    entry.time = time++;
    entry.usage++;
    ordering.add(entry);
  }

  public static void main(String[] args) {
    System.out.println("Please run this solution on LeetCode.");
    System.out.println("https://leetcode.com/problems/lfu-cache/");
  }
}
