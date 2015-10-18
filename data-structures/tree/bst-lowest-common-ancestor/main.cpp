#include <iostream>

using namespace std;

typedef struct node
{
   int data;
   node* left;
   node* right;
} node;

node* lca(node* root, int v1, int v2);
node* lca_helper(node* root, int v1, int v2);
bool contains(node* root, int data);

node* lca(node* root, int v1, int v2)
{
    if (!contains(root, v1) || !contains(root, v2)) {
        return NULL;
    }
    return lca_helper(root, v1, v2);
}

node* lca_helper(node* root, int v1, int v2)
{
    if (root == NULL) {
        return NULL;
    }

    if (root->data == v1 || root->data == v2) {
        return root;
    }

    bool v1OnLeft = contains(root->left, v1);
    bool v2OnLeft = contains(root->left, v2);

    if (v1OnLeft != v2OnLeft) {
        return root;
    }

    root = v1OnLeft == true ? root->left : root->right;
    return lca_helper(root, v1, v2);
}

bool contains(node* root, int data)
{
    if (root == NULL) {
        return false;
    }
    if (root->data == data) {
        return true;
    }
    return contains(root->left, data) || contains(root->right, data);
}

int main()
{
    node left = { 1 };
    node right = { 3 };
    node root = {
        2,
        &left,
        &right
    };

    node* ancestor = lca(&root, 1, 3);

    if (ancestor == &root) {
        cout << "Lowest common ancestor of 1 and 3 is " << ancestor->data << endl;
    } else {
        cerr << "An error occurred!" << endl;
    }

    return 0;
}
