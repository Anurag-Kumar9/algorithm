#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class AVLNode {
public:
    int data;
    AVLNode* left;
    AVLNode* right;
    int height;
    AVLNode(int data) {
        this->data = data;
        left = right = nullptr;
        height = 1;
    }
};

class AVLTree {
private:
    AVLNode* root;

    int height(AVLNode* node) {
        return node ? node->height : 0;
    }

    int getBalance(AVLNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    AVLNode* insert(AVLNode* node, int data) {
        if (!node) return new AVLNode(data);
        if (data < node->data)
            node->left = insert(node->left, data);
        else if (data > node->data)
            node->right = insert(node->right, data);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        if (balance > 1 && data < node->left->data)
            return rightRotate(node);
        if (balance < -1 && data > node->right->data)
            return leftRotate(node);
        if (balance > 1 && data > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && data < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inOrderTraversal(AVLNode* node, vector<int>& elements) {
        if (node) {
            inOrderTraversal(node->left, elements);
            elements.push_back(node->data);
            inOrderTraversal(node->right, elements);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int data) {
        root = insert(root, data);
    }

    void inOrderTraversal(vector<int>& elements) {
        inOrderTraversal(root, elements);
    }

    AVLNode* getRoot() {
        return root;
    }

    void setRoot(AVLNode* node) {
        root = node;
    }

    AVLNode* sortedArrayToAVL(vector<int>& elements, int start, int end) {
        if (start > end) return nullptr;
        int mid = (start + end) / 2;
        AVLNode* node = new AVLNode(elements[mid]);
        node->left = sortedArrayToAVL(elements, start, mid - 1);
        node->right = sortedArrayToAVL(elements, mid + 1, end);
        node->height = 1 + max(height(node->left), height(node->right));
        return node;
    }
};

AVLTree mergeAVL(AVLTree& tree1, AVLTree& tree2) {
    vector<int> elements1, elements2, mergedElements;
    tree1.inOrderTraversal(elements1);
    tree2.inOrderTraversal(elements2);

    // Merge the two sorted arrays
    mergedElements.reserve(elements1.size() + elements2.size());
    merge(elements1.begin(), elements1.end(), elements2.begin(), elements2.end(), back_inserter(mergedElements));

    // Create a new AVL tree from the merged sorted array
    AVLTree mergedTree;
    mergedTree.setRoot(mergedTree.sortedArrayToAVL(mergedElements, 0, mergedElements.size() - 1));
    return mergedTree;
}

int main() {
    AVLTree tree1, tree2;
    tree1.insert(10);
    tree1.insert(20);
    tree1.insert(30);

    tree2.insert(15);
    tree2.insert(25);
    tree2.insert(35);

    AVLTree mergedTree = mergeAVL(tree1, tree2);

    cout << "Inorder traversal of the merged AVL tree is \n";
    vector<int> elements;
    mergedTree.inOrderTraversal(elements);
    for (int val : elements) {
        cout << val << " ";
    }

    return 0;
}