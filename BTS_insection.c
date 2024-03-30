#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int key) {
    if (root == NULL) {
        return createNode(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }

    return root;
}

void preOrderTraversal(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

int main() {
    struct Node* root = NULL;
    char command[10];
    int key;

    while (scanf("%s", command) == 1 && command[0] != '#') {
        if (scanf("%d", &key) == 1) {
            if (strcmp(command, "insert") == 0) {
                root = insert(root, key);
            }
        }
    }

    preOrderTraversal(root);

    return 0;
}
