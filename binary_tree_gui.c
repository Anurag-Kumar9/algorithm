#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node *root = NULL;

Node *createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node *insert(Node *root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}

void insertLeftmost(Node **root, int data) {
    Node *newNode = createNode(data);
    if (*root == NULL) {
        *root = newNode;
    } else {
        Node *current = *root;
        while (current->left != NULL) {
            current = current->left;
        }
        current->left = newNode;
    }
}

void insertRightmost(Node **root, int data) {
    Node *newNode = createNode(data);
    if (*root == NULL) {
        *root = newNode;
    } else {
        Node *current = *root;
        while (current->right != NULL) {
            current = current->right;
        }
        current->right = newNode;
    }
}

int countNodes(Node *root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

void insertMiddle(Node **root, int data) {
    if (*root == NULL) {
        *root = createNode(data);
        return;
    }

    Node *current = *root;
    Node *parent = NULL;

    while (current != NULL) {
        parent = current;
        int leftCount = countNodes(current->left);
        int rightCount = countNodes(current->right);

        if (leftCount <= rightCount) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (parent->left == NULL) {
        parent->left = createNode(data);
    } else {
        parent->right = createNode(data);
    }
}

void inorderTraversal(Node *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

void generateDotFile(Node *root, FILE *file) {
    if (root == NULL) return;

    if (root->left) {
        fprintf(file, "    %d -> %d [label=\"left\"];\n", root->data, root->left->data);
        generateDotFile(root->left, file);
    }
    if (root->right) {
        fprintf(file, "    %d -> %d [label=\"right\"];\n", root->data, root->right->data);
        generateDotFile(root->right, file);
    }
}

void writeDotFile() {
    FILE *file = fopen("bst.dot", "w");
    if (file == NULL) {
        perror("Unable to open file");
        exit(1);
    }

    fprintf(file, "digraph BST {\n");
    fprintf(file, "    node [shape=record, fontsize=12, fontname=\"Arial\"];\n");
    generateDotFile(root, file);
    fprintf(file, "}\n");

    fclose(file);
}

int main() {
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insertLeftmost(&root, 10);
    insertRightmost(&root, 90);
    insertMiddle(&root, 35);

    printf("In-order traversal :\n");
    inorderTraversal(root);
    printf("\n");

    writeDotFile();

    system("dot -Tpng bst.dot -o bst.png");

    return 0;
}