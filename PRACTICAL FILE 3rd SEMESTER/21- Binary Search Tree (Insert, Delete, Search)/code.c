/*
    DSA Practical 21: Binary Search Tree (Insert, Delete, Search)
    ----------------------------------------------------
    Compile : gcc bst_operations.c -o bst_operations
    Run     : ./bst_operations
*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int d;
    struct Node *l, *r;
};

struct Node* newNode(int v) {
    struct Node *n = (struct Node *)malloc(sizeof(struct Node));
    n->d = v;
    n->l = n->r = NULL;
    return n;
}

struct Node* insert(struct Node* root, int v) {
    if (root == NULL) return newNode(v);
    if (v < root->d) root->l = insert(root->l, v);
    else if (v > root->d) root->r = insert(root->r, v);
    return root;
}

struct Node* findMin(struct Node* root) {
    while (root->l != NULL) root = root->l;
    return root;
}

struct Node* deleteNode(struct Node* root, int v) {
    if (root == NULL) return root;

    if (v < root->d) {
        root->l = deleteNode(root->l, v);
    } else if (v > root->d) {
        root->r = deleteNode(root->r, v);
    } else {
        if (root->l == NULL) {
            struct Node* t = root->r;
            free(root);
            return t;
        } else if (root->r == NULL) {
            struct Node* t = root->l;
            free(root);
            return t;
        }
        struct Node* t = findMin(root->r);
        root->d = t->d;
        root->r = deleteNode(root->r, t->d);
    }
    return root;
}

struct Node* search(struct Node* root, int v) {
    if (root == NULL || root->d == v) return root;
    if (v < root->d) return search(root->l, v);
    return search(root->r, v);
}

void inorder(struct Node* root) {
    if (root == NULL) return;
    inorder(root->l);
    printf("%d ", root->d);
    inorder(root->r);
}

int main() {
    struct Node* root = NULL;
    int ch, v;

    do {
        printf("\n----- BST OPERATIONS MENU -----\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Inorder Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &v);
                root = insert(root, v);
                printf("%d inserted.\n", v);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &v);
                root = deleteNode(root, v);
                printf("%d deleted (if it existed).\n", v);
                break;
            case 3:
                printf("Enter value to search: ");
                scanf("%d", &v);
                if (search(root, v) != NULL)
                    printf("%d found in BST.\n", v);
                else
                    printf("%d not found in BST.\n", v);
                break;
            case 4:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (ch != 5);

    return 0;
}