#include <iostream>
#include <algorithm>

using std::max;

#define DEV true

#if DEV
struct node {
  int val;
  node* left;
  node* right;
  int ht;
};
#endif

//
// Returns the height of the tree or -1 if the tree is empty.
//
inline int get_height(node* root) {
  return (root != nullptr) ? root->ht : -1;
}

//
// Calculates and updates the height of the tree using the heights of the
// children.
//
inline void update_height(node* root) {
    root->ht = 1 + max(get_height(root->left), get_height(root->right));
}

//
// Returns how left or right heavy the tree is.
//
inline int weight(node* root) {
    if (root == nullptr) {
        return 0;
    }
    return get_height(root->left) - get_height(root->right);
}

//
// Left rotates the tree.
//
node* left_rotate(node* root) {
    node* r = root->right;  // This will be the new root.
    node* rl = r->left;

    root->right = rl;
    update_height(root);

    r->left = root;
    update_height(r);
    return r;
}

//
// Right rotates the tree.
//
node* right_rotate(node* root) {
    node* l = root->left;  // This will be the new root.
    node* lr = l-> right;

    root->left = lr;
    update_height(root);

    l->right = root;
    update_height(l);
    return l;
}

//
// Inserts a value into the tree. Values in the left sub-tree are less than the
// root and values in the right sub-tree are greater than or equal to the root.
//
node* insert(node* root, int value) {
    if (root == nullptr) {
        return new node {value, nullptr, nullptr, 0};
    }

    // Insert value into the correct sub-tree.
    if (value < root->val) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }

    // Rebalance the tree after insertion.
    int w = weight(root);
    if (w > 1) {
        // Root is left heavy.
        if (weight(root->left) < 0) {
            // Left child is right heavy.
            root->left = left_rotate(root->left);
        }
        root = right_rotate(root);
    } else if (w < -1) {
        // Root is right heavy.
        if (weight(root->right) > 0) {
            // Right child is left heavy.
            root->right = right_rotate(root->right);
        }
        root = left_rotate(root);
    }

    update_height(root);
    return root;
}

#if DEV
node* create(int value) {
  return new node {value, nullptr, nullptr, 0};
}

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
  node* root = create(3);
  root = insert(root, 2);
  root = insert(root, 4);
  root = insert(root, 5);
  root = insert(root, 6);

  // Manually create a tree to test against...
  node* three = create(3);
  three->left = create(2);

  node* five = create(5);
  five->left = create(4);
  five->right = create(6);

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
