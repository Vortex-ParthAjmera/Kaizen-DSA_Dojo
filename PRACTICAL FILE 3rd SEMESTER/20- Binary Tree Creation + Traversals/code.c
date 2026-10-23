/*
    DSA Practical 20: Binary Tree Creation + Traversals
    (Inorder, Preorder, Postorder)
    ----------------------------------------------------
    Compile : gcc binary_tree_traversals.c -o binary_tree_traversals
    Run     : ./binary_tree_traversals
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
    else root->r = insert(root->r, v);
    return root;
}

void inorder(struct Node* root) {
    if (root == NULL) return;
    inorder(root->l);
    printf("%d ", root->d);
    inorder(root->r);
}

void preorder(struct Node* root) {
    if (root == NULL) return;
    printf("%d ", root->d);
    preorder(root->l);
    preorder(root->r);
}

void postorder(struct Node* root) {
    if (root == NULL) return;
    postorder(root->l);
    postorder(root->r);
    printf("%d ", root->d);
}

int main() {
    struct Node* root = NULL;
    int n, v;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter value %d: ", i + 1);
        scanf("%d", &v);
        root = insert(root, v);
    }

    printf("Inorder   : "); inorder(root);   printf("\n");
    printf("Preorder  : "); preorder(root);  printf("\n");
    printf("Postorder : "); postorder(root); printf("\n");

    return 0;
}