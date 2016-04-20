#include <iostream>

#define DEV 1

#if DEV
struct node {
  int val;
  node* left = nullptr;
  node* right = nullptr;
  int ht = 0;
};
#endif

node* create_node(int val) {
  node* n = new node;
  n->val = val;
  return n;
}

int height(const node* n) {
  return n == nullptr ? -1 : n->ht;
}

int calc_height(const node* n) {
  return 1 + std::max(height(n->left), height(n->right));
}

int weight(const node* n) {
  if (n == nullptr) {
    return 0;
  }
  return height(n->left) - height(n->right);
}

node* right_rotate(node* root) {
  node* original = root;
  root = original->left;
  original->left = root->right;
  root->right = original;

  original->ht = calc_height(original);
  root->ht = calc_height(root);

  return root;
}

node* left_rotate(node* root) {
  node* original = root;
  root = original->right;
  original->right = root->left;
  root->left = original;

  original->ht = calc_height(original);
  root->ht = calc_height(root);

  return root;
}

node* balance(node* root) {
  int w = weight(root);
  if (root == nullptr || std::abs(w) <= 1) {
    return root;
  }

  if (w > 0) {
    if (weight(root->left) < 0) {
      root->left = left_rotate(root->left);
    }
    return right_rotate(root);
  } else {
    if (weight(root->right) > 0) {
      root->right = right_rotate(root->right);
    }
    return left_rotate(root);
  }
}

node* insert(node* root, int value) {
  if (value < root->val) {
    if (root->left == nullptr) {
      root->left = create_node(value);
    } else {
      root->left = insert(root->left, value);
    }
  } else if (value > root->val) {
    if (root->right == nullptr) {
      root->right = create_node(value);
    } else {
      root->right = insert(root->right, value);
    }
  }
  root->ht = calc_height(root);
  return balance(root);
}

#if DEV
bool equal(node* a, node* b) {
  if (a == nullptr && b == nullptr) {
    return true;
  } else if (a == nullptr || b == nullptr || a->val != b->val) {
    return false;
  }

  return equal(a->left, b->left) && equal(a->right, b->right);
}

int main() {
  // Create the AVL tree...
  node* root = create_node(3);
  root = insert(root, 2);
  root = insert(root, 4);
  root = insert(root, 5);
  root = insert(root, 6);

  // Manually create a tree to test against...
  node* three = create_node(3);
  three->left = create_node(2);

  node* five = create_node(5);
  five->left = create_node(4);
  five->right = create_node(6);

  three->right = five;

  // Check if the AVL tree is equal to the reference tree...
  if (equal(root, three)) {
    std::cout << "AVL tree is balanced!" << std::endl;
  } else {
    std::cout << "AVL tree is not balanced!" << std::endl;
  }

  return 0;
}
#endif
