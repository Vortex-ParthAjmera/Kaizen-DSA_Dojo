/*
    DSA Practical 3: Doubly Linked List Operations
    Perform Insertion (Beginning, Middle, End)
    and Deletion (Beginning, Middle, End) in a Doubly Linked List
    ----------------------------------------------------
    Compile : gcc doubly_linked_list_operations.c -o doubly_linked_list_operations
    Run     : ./doubly_linked_list_operations
*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
};

struct Node *head = NULL;

void insertBeginningValue(int value);   // forward declaration
void insertEndValue(int value);         // forward declaration

// -------------------- INSERT AT BEGINNING --------------------
void insertBeginningValue(int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = head;

    if (head != NULL) {
        head->prev = newNode;
    }
    head = newNode;
}

void insertBeginning() {
    int value;
    printf("Enter value to insert: ");
    scanf("%d", &value);

    insertBeginningValue(value);

    printf("%d inserted at beginning.\n", value);
}

// -------------------- INSERT AT END --------------------
void insertEndValue(int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    if (head == NULL) {
        newNode->prev = NULL;
        head = newNode;
    } else {
        struct Node *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}

void insertEnd() {
    int value;
    printf("Enter value to insert: ");
    scanf("%d", &value);

    insertEndValue(value);

    printf("%d inserted at end.\n", value);
}

// -------------------- INSERT AT MIDDLE (given position) --------------------
void insertMiddle() {
    int value, pos;
    printf("Enter value to insert: ");
    scanf("%d", &value);
    printf("Enter position to insert at: ");
    scanf("%d", &pos);

    if (pos == 1) {
        insertBeginningValue(value);
        printf("%d inserted at position 1.\n", value);
        return;
    }

    struct Node *temp = head;
    for (int i = 1; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Invalid position.\n");
        return;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = temp->next;
    newNode->prev = temp;

    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;

    printf("%d inserted at position %d.\n", value, pos);
}

// -------------------- DELETE AT BEGINNING --------------------
void deleteBeginning() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node *temp = head;
    head = head->next;
    if (head != NULL) {
        head->prev = NULL;
    }

    printf("%d deleted from beginning.\n", temp->data);
    free(temp);
}

// -------------------- DELETE AT END --------------------
void deleteEnd() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    if (head->next == NULL) {
        printf("%d deleted from end.\n", head->data);
        free(head);
        head = NULL;
        return;
    }

    struct Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    printf("%d deleted from end.\n", temp->data);
    temp->prev->next = NULL;
    free(temp);
}

// -------------------- DELETE AT MIDDLE (given position) --------------------
void deleteMiddle() {
    int pos;
    printf("Enter position to delete: ");
    scanf("%d", &pos);

    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    if (pos == 1) {
        deleteBeginning();
        return;
    }

    struct Node *temp = head;
    for (int i = 1; i < pos && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Invalid position.\n");
        return;
    }

    temp->prev->next = temp->next;
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

    printf("%d deleted from position %d.\n", temp->data, pos);
    free(temp);
}

// -------------------- DISPLAY --------------------
void display() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node *temp = head;
    printf("List elements: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// -------------------- MAIN MENU --------------------
int main() {
    int choice;

    // ---- build initial list from user input ----
    int count;
    printf("Enter initial number of nodes: ");
    scanf("%d", &count);

    for (int i = 0; i < count; i++) {
        int val;
        printf("Enter element %d: ", i + 1);
        scanf("%d", &val);
        insertEndValue(val);
    }

    do {
        printf("\n----- DOUBLY LINKED LIST OPERATIONS MENU -----\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at Middle\n");
        printf("3. Insert at End\n");
        printf("4. Delete at Beginning\n");
        printf("5. Delete at Middle\n");
        printf("6. Delete at End\n");
        printf("7. Display\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
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

    } while (choice != 8);

    return 0;
}