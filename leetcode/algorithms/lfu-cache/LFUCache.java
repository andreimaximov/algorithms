import java.util.TreeSet;
import java.util.HashMap;

//
// Simple O(logn) LFU cache implementation using balanced trees.
//
class SimpleLFUCache {
  //
  // Represents a (key, value) pair for every entry in the cache.
  //
  private class Entry implements Comparable<Entry> {
    public int key;

    public int value;

    //
    // Access count for the key since it was first inserted.
    //
    public int count;

    //
    // Last set/get time for the key.
    //
    public int time;

    public Entry(int key, int value) {
      this.key = key;
      this.value = value;
      this.count = 0;
      this.time = SimpleLFUCache.this.time++;
    }

    //
    // Compares entries by usage and timestamp. To modify an entry, you can
    // remove it from the tree set, update it, and add it back. This will work
    // because the usage and timestamp information will uniquely identify the
    // entry if left untouched.
    //
    public int compareTo(Entry other) {
      if (count < other.count) {
        return -1;
      } else if (count == other.count) {
        return time - other.time;
      }
      return 1;
    }
  }

  private TreeSet<Entry> ordering = new TreeSet<>();

  private HashMap<Integer, Entry> index = new HashMap<>();

  private int capacity;

  private int time;

  public SimpleLFUCache(int capacity) {
    this.capacity = Math.max(capacity, 0);
  }

  //
  // Returns the value associated with the key. Returns -1 if the value does
  // not exceed due to purging of the key or never being set.
  //
  public int get(int key) {
    if (!index.containsKey(key)) {
      return -1;
    }
    Entry entry = index.get(key);
    ping(entry);
    return entry.value;
  }

  //
  // Sets the value for they key and purges according to FSU policy if capacity
  // is exceeded.
  //
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
    entry.count++;
    ordering.add(entry);
  }
}

//
// Slightly more complex O(1) LFU cache implementation using linked hash maps.
//
public class LFUCache {
  //
  // Represents an entry for a (key, value) pair in the cache.
  //
  private static class Entry {
    public int key;

    public int value;

    public int count = 1;

    //
    // Link to previous entry in the same access count bucket.
    //
    public Entry last;

    //
    // Link to next entry in the same access count bucket.
    //
    public Entry next;

    public Entry(int key, int value) {
      this.key = key;
      this.value = value;
    }
  }

  //
  // Linked list of entries with the same access count.
  //
  private static class Bucket {
    public Entry head;

    public Entry tail;

    //
    // Link to previous bucket with a lower count.
    //
    public Bucket last;

    //
    // Link to the nexy bucket with a higher count.
    //
    public Bucket next;

    public int count;

    public Bucket(int count) {
      this.count = count;
    }
  }

  //
  // Map from usage count to a bucket of entries with the same access count.
  //
  private HashMap<Integer, Bucket> buckets = new HashMap<>();

  //
  // Map from key to corresponding entry.
  //
  private HashMap<Integer, Entry> entries = new HashMap<>();

  private int size = 0;

  private int capacity;

  public LFUCache(int capacity) {
    this.capacity = capacity;
    this.buckets.put(0, new Bucket(0));
  }

  //
  // Returns the value associated with the key. Returns -1 if the value does
  // not exceed due to purging of the key or never being set.
  //
  public int get(int key) {
    if (!entries.containsKey(key)) {
      return -1;
    }
    return ping(key).value;
  }

  //
  // Sets the value for they key and purges according to FSU policy if capacity
  // is exceeded.
  //
  public void set(int key, int value) {
    if (entries.containsKey(key)) {
      ping(key).value = value;
    } else {
      if (capacity == 0) {
        return;
      } else if (size == capacity) {
        // Get the first entry in the first non-zero count bucket.
        Entry entry = buckets.get(0).next.head;
        remove(entry);
        clean(entry.count);
      }
      Entry entry = new Entry(key, value);
      insert(entry);
    }
  }

  //
  // Pings an entry for a particular key increasing it's access count. Returns
  // a reference to the entry.
  //
  private Entry ping(int key) {
    Entry entry = entries.get(key);
    remove(entry);
    entry.count++;
    insert(entry);
    clean(entry.count - 1);
    return entry;
  }

  //
  // Gets the insertion bucket for the entry. Bucket for count entry.count must
  // exist for linking to work.
  //
  private Bucket getBucket(Entry entry) {
    if (!buckets.containsKey(entry.count)) {
      Bucket current = new Bucket(entry.count);
      buckets.put(entry.count, current);

      // Setup link to last.
      current.last = buckets.get(entry.count - 1);

      // Update the next link.
      if (current.last.next != null) {
        current.last.next.last = current;
        current.next = current.last.next;
      }

      // Update prev link
      current.last.next = current;
    }

    return buckets.get(entry.count);
  }

  //
  // Inserts the entry into a bucket.
  //
  private void insert(Entry entry) {
    Bucket bucket = getBucket(entry);
    if (bucket.head == null) {
      bucket.head = entry;
      bucket.tail = entry;
      entry.last = null;
    } else {
      entry.last = bucket.tail;
      bucket.tail.next = entry;
      bucket.tail = entry;
    }
    entry.next = null;
    entries.put(entry.key, entry);
    size++;
  }

  //
  // Removes the entry from its bucket.
  //
  private void remove(Entry entry) {
    Bucket bucket = buckets.get(entry.count);

    // Remove entry from bucket
    if (bucket.head == entry) {
      bucket.head = bucket.head.next;
    }
    if (bucket.tail == entry) {
      bucket.tail = bucket.tail.last;
    }

    // Fix up entry last/next links
    if (entry.last != null) {
      entry.last.next = entry.next;
    }
    if (entry.next != null) {
      entry.next.last = entry.last;
    }

    entries.remove(entry.key);
    size--;
  }

  //
  // Cleans up/removes the bucket for the specified count if it is empty.
  //
  private void clean(int count) {
    Bucket bucket = buckets.get(count);

    if (bucket.head == null) {

      // Fix up bucket last/next links
      if (bucket.last != null) {
        bucket.last.next = bucket.next;
      }

      if (bucket.next != null) {
        bucket.next.last = bucket.last;
      }

      buckets.remove(count);
    }
  }

  public static void main(String[] args) {
    LFUCache cache = new LFUCache(3);
    cache.set(2, 2);
    cache.set(1, 1);
    get(cache, 2, 2);
    get(cache, 1, 1);
    get(cache, 2, 2);
    cache.set(3, 3);
    cache.set(4, 4);
    get(cache, 3, -1);
    get(cache, 2, 2);
    get(cache, 1, 1);
    get(cache, 4, 4);

    System.out.println("Tests pass!");
    System.out.println("Please run this solution on LeetCode.");
    System.out.println("https://leetcode.com/problems/lfu-cache/");
  }

  public static void get(LFUCache cache, int key, int value) {
    assert cache.get(key) == value;
  }
}
