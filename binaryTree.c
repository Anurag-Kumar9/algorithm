#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insertBST(struct Node* root, struct Node* newNode) {
    if(root == NULL) {
        root = newNode;
        return newNode;
    }
    if(newNode->data < root->data) {
        root->left = insertBST(root->left, newNode);
    }
    else {
        root->right = insertBST(root->right, newNode);
    }
    return root;
}

void inorderTraversal(struct Node* root, int arr[], int *i) {
    if(root == NULL) {
        return;
    }
    inorderTraversal(root->left, arr, i);
    arr[(*i)++] = root->data;
    inorderTraversal(root->right, arr, i);
}

int main() {
    struct Node* root = NULL;
    printf("Enter the value of node to be inserted in binary search tree: \nPress -1 to exit\n");
    int value, n = 0;
    do {
        printf("Enter the value of node to be inserted in binary search tree: ");
        scanf("%d", &value);
        if (value != -1) {
            n++;
            struct Node* newNode = createNode(value);
            root = insertBST(root, newNode);
        }
    } while (value != -1);
    int *arr = (int *)malloc(n*sizeof(int));
    int i = 0;
    inorderTraversal(root, arr, &i);
    int j;
    for(j= 0; j < n; j++) {
        printf("%d ", arr[j]);
    }
    printf("\n");

    int k;
    printf("Enter the value of k to get kth element: ");
    scanf("%d", &k);
    printf("kth element is %d", arr[k - 1]);
}

