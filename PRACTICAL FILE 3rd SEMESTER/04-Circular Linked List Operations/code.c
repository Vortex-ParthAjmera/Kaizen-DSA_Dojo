/*
    DSA Practical 4: Circular Linked List Operations
    Insertion & Deletion (Beginning, Middle, End)
    ----------------------------------------------------
    Compile : gcc circular_linked_list_operations.c -o circular_linked_list_operations
    Run     : ./circular_linked_list_operations
*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int d;          // data
    struct Node *n; // next
};

struct Node *h = NULL;   // head

void insertBeginningValue(int v);   // forward declaration
void insertEndValue(int v);         // forward declaration

// -------------------- LENGTH --------------------
int listLength() {
    if (h == NULL) return 0;
    int c = 1;
    struct Node *t = h;
    while (t->n != h) {
        c++;
        t = t->n;
    }
    return c;
}

// -------------------- INSERT AT BEGINNING --------------------
void insertBeginningValue(int v) {
    struct Node *nn = (struct Node *)malloc(sizeof(struct Node));
    nn->d = v;

    if (h == NULL) {
        nn->n = nn;
        h = nn;
        return;
    }

    struct Node *l = h;
    while (l->n != h) l = l->n;

    nn->n = h;
    h = nn;
    l->n = h;
}

void insertBeginning() {
    int v;
    printf("Enter value to insert: ");
    scanf("%d", &v);
    insertBeginningValue(v);
    printf("%d inserted at beginning.\n", v);
}

// -------------------- INSERT AT END --------------------
void insertEndValue(int v) {
    struct Node *nn = (struct Node *)malloc(sizeof(struct Node));
    nn->d = v;

    if (h == NULL) {
        nn->n = nn;
        h = nn;
        return;
    }

    struct Node *l = h;
    while (l->n != h) l = l->n;

    l->n = nn;
    nn->n = h;
}

void insertEnd() {
    int v;
    printf("Enter value to insert: ");
    scanf("%d", &v);
    insertEndValue(v);
    printf("%d inserted at end.\n", v);
}

// -------------------- INSERT AT MIDDLE (given position) --------------------
void insertMiddle() {
    int v, p;
    printf("Enter value to insert: ");
    scanf("%d", &v);
    printf("Enter position to insert at: ");
    scanf("%d", &p);

    int ln = listLength();

    if (p == 1) {
        insertBeginningValue(v);
        printf("%d inserted at position 1.\n", v);
        return;
    }

    if (p < 1 || p > ln + 1) {
        printf("Invalid position.\n");
        return;
    }

    struct Node *t = h;
    for (int i = 1; i < p - 1; i++) {
        t = t->n;
    }

    struct Node *nn = (struct Node *)malloc(sizeof(struct Node));
    nn->d = v;
    nn->n = t->n;
    t->n = nn;

    printf("%d inserted at position %d.\n", v, p);
}

// -------------------- DELETE AT BEGINNING --------------------
void deleteBeginning() {
    if (h == NULL) {
        printf("List is empty.\n");
        return;
    }

    if (h->n == h) {
        printf("%d deleted from beginning.\n", h->d);
        free(h);
        h = NULL;
        return;
    }

    struct Node *t = h;
    struct Node *l = h;
    while (l->n != h) l = l->n;

    h = h->n;
    l->n = h;

    printf("%d deleted from beginning.\n", t->d);
    free(t);
}

// -------------------- DELETE AT END --------------------
void deleteEnd() {
    if (h == NULL) {
        printf("List is empty.\n");
        return;
    }

    if (h->n == h) {
        printf("%d deleted from end.\n", h->d);
        free(h);
        h = NULL;
        return;
    }

    struct Node *t = h;
    while (t->n->n != h) {
        t = t->n;
    }

    printf("%d deleted from end.\n", t->n->d);
    free(t->n);
    t->n = h;
}

// -------------------- DELETE AT MIDDLE (given position) --------------------
void deleteMiddle() {
    int p;
    printf("Enter position to delete: ");
    scanf("%d", &p);

    if (h == NULL) {
        printf("List is empty.\n");
        return;
    }

    int ln = listLength();

    if (p < 1 || p > ln) {
        printf("Invalid position.\n");
        return;
    }

    if (p == 1) {
        deleteBeginning();
        return;
    }

    struct Node *t = h;
    for (int i = 1; i < p - 1; i++) {
        t = t->n;
    }

    struct Node *td = t->n;
    t->n = td->n;

    printf("%d deleted from position %d.\n", td->d, p);
    free(td);
}

// -------------------- DISPLAY --------------------
void display() {
    if (h == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node *t = h;
    printf("List elements: ");
    do {
        printf("%d ", t->d);
        t = t->n;
    } while (t != h);
    printf("\n");
}

// -------------------- MAIN MENU --------------------
int main() {
    int ch;

    int c;
    printf("Enter initial number of nodes: ");
    scanf("%d", &c);

    for (int i = 0; i < c; i++) {
        int v;
        printf("Enter element %d: ", i + 1);
        scanf("%d", &v);
        insertEndValue(v);
    }

    do {
        printf("\n----- CIRCULAR LINKED LIST OPERATIONS MENU -----\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at Middle\n");
        printf("3. Insert at End\n");
        printf("4. Delete at Beginning\n");
        printf("5. Delete at Middle\n");
        printf("6. Delete at End\n");
        printf("7. Display\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: insertBeginning(); break;
            case 2: insertMiddle(); break;
            case 3: insertEnd(); break;
            case 4: deleteBeginning(); break;
            case 5: deleteMiddle(); break;
            case 6: deleteEnd(); break;
            case 7: display(); break;
            case 8: printf("Exiting program.\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }

    } while (ch != 8);

    return 0;
}