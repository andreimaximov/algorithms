import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

class Vertex {
  protected int value;

  protected int weight;

  protected List<Vertex> connections;

  public Vertex(int value) {
    this.value = value;
    this.weight = 0;
    this.connections = new LinkedList<Vertex>();
  }

  public void connectWith(Vertex vertex) {
    this.connections.add(vertex);
    vertex.connections.add(this);
  }

  public int calculateWeight() {
    return this.doCalculateWeight(null);
  }

  protected int doCalculateWeight(Vertex parent) {
    this.weight = this.value;
    for(Vertex vertex : this.connections) {
      if (vertex == parent) {
        continue;
      }
      this.weight += vertex.doCalculateWeight(this);
    }
    return this.weight;
  }

  public int calculateSmallestDiff() {
    return this.doCalculateSmallestDiff(null, this);
  }

  protected int doCalculateSmallestDiff(Vertex parent, Vertex root) {
    int bestDiff = -1;
    if (this != root) {
      bestDiff = Math.abs(root.weight - 2 * this.weight);
    }
    for (Vertex vertex : this.connections) {
      if (vertex == parent) {
        continue;
      }
      int diff = vertex.doCalculateSmallestDiff(this, root);
      if (bestDiff == -1 || diff < bestDiff) {
        bestDiff = diff;
      }
    }
    return bestDiff;
  }
}

public class Solution {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    int n = Integer.parseInt(scanner.nextLine());

    // Create all the vertices first.
    Vertex[] vertices = new Vertex[n];
    for (int i = 0; i < n; ++i) {
      vertices[i] = new Vertex(scanner.nextInt());
    }
    scanner.nextLine();

    // Connect the vertices.
    int parent, child;
    while (n > 1) {
      parent = scanner.nextInt() - 1;
      child = scanner.nextInt() - 1;
      vertices[parent].connectWith(vertices[child]);
      n--;
    }

    // Calculate the weights of all the vertices.
    Vertex root = vertices[0];
    root.calculateWeight();

    // Calculate the smallest possible difference when removing an edge.
    System.out.println(root.calculateSmallestDiff());
  }
}
