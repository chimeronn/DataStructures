#include <iostream>
#include <vector>
using namespace std;

struct Node {
  public:
    int key;
    Node* left;
    Node* right;

    Node(int key) {
      this->key = key;
      left = nullptr;
      right = nullptr;
    }

    Node* insert(Node* node, int key) {
      if(node == NULL) return new Node(key);
      if(key <= node->key) {
        node->left = insert(node->left, key);
        cout << key << " " << node->key << endl;
      }
      else node->right = insert(node->right, key);
      return node;
    }

    void inorder(Node* root) {
        if (root != NULL) {
            inorder(root->left);
            cout << root->key << " ";
            inorder(root->right);
        }
    }
};

int main() {
  Node* root = new Node(50);
  root->insert(root, 30);
  root->insert(root, 20);
  root->insert(root, 40);
  root->insert(root, 70);
  root->insert(root, 60);
  root->insert(root, 80);

  // Print inorder traversal of the BST
  root->inorder(root);
}
