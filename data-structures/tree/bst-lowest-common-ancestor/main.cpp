#include <iostream>

#define DEV 1

#if DEV
struct node {
  int data;
  node* left;
  node* right;
};
#endif

bool contains(node* root, int value) {
  if (root == nullptr) {
    return false;
  } else if (root->data == value) {
    return true;
  } else if (root->data < value) {
    return contains(root->right, value);
  } else {
    return contains(root->left, value);
  }
}

node* lca_helper(node* root, int a, int b) {
  if (root == nullptr) {
    return nullptr;
  }

  if (root->data == a || root->data == b) {
    return root;
  }

  bool left = contains(root->left, a);

  if (left != contains(root->left, b)) {
    return root;
  }

  root = left == true ? root->left : root->right;
  return lca_helper(root, a, b);
}

node* lca(node* root, int a, int b) {
  if (!contains(root, a) || !contains(root, b)) {
    return nullptr;
  }
  return lca_helper(root, a, b);
}

#if DEV
int main() {
  node left {1};
  node right {3};
  node root {2, &left, &right};

  node* ancestor = lca(&root, 1, 3);
  if (ancestor == &root) {
    std::cout << "LCA of 1 and 3 is " << ancestor->data << std::endl;
  } else {
    std::cerr << "Error!" << std::endl;
  }

  return 0;
}
#endif
