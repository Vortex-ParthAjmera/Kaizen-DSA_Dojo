/*
    DSA Practical 5: Circular Doubly Linked List Operations
    Perform Insertion (Beginning, Middle, End)
    and Deletion (Beginning, Middle, End) in a Circular Doubly Linked List
    ----------------------------------------------------
    Compile : gcc circular_doubly_linked_list_operations.c -o circular_doubly_linked_list_operations
    Run     : ./circular_doubly_linked_list_operations
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

// -------------------- HELPER: LENGTH --------------------
int listLength() {
    if (head == NULL) {
        return 0;
    }
    int count = 1;
    struct Node *temp = head;
    while (temp->next != head) {
        count++;
        temp = temp->next;
    }
    return count;
}

// -------------------- INSERT AT BEGINNING --------------------
void insertBeginningValue(int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;

    if (head == NULL) {
        newNode->next = newNode;
        newNode->prev = newNode;
        head = newNode;
        return;
    }

    struct Node *last = head->prev;

    newNode->next = head;
    newNode->prev = last;
    last->next = newNode;
    head->prev = newNode;

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

    if (head == NULL) {
        newNode->next = newNode;
        newNode->prev = newNode;
        head = newNode;
        return;
    }

    struct Node *last = head->prev;

    newNode->next = head;
    newNode->prev = last;
    last->next = newNode;
    head->prev = newNode;
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

    int len = listLength();

    if (pos == 1) {
        insertBeginningValue(value);
        printf("%d inserted at position 1.\n", value);
        return;
    }

    if (pos < 1 || pos > len + 1) {
        printf("Invalid position.\n");
        return;
    }

    struct Node *temp = head;
    for (int i = 1; i < pos - 1; i++) {
        temp = temp->next;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = temp->next;
    newNode->prev = temp;
    temp->next->prev = newNode;
    temp->next = newNode;

    printf("%d inserted at position %d.\n", value, pos);
}

// -------------------- DELETE AT BEGINNING --------------------
void deleteBeginning() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    if (head->next == head) {
        printf("%d deleted from beginning.\n", head->data);
        free(head);
        head = NULL;
        return;
    }

    struct Node *temp = head;
    struct Node *last = head->prev;

    head = head->next;
    head->prev = last;
    last->next = head;

    printf("%d deleted from beginning.\n", temp->data);
    free(temp);
}

// -------------------- DELETE AT END --------------------
void deleteEnd() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    if (head->next == head) {
        printf("%d deleted from end.\n", head->data);
        free(head);
        head = NULL;
        return;
    }

    struct Node *last = head->prev;
    struct Node *newLast = last->prev;

    newLast->next = head;
    head->prev = newLast;

    printf("%d deleted from end.\n", last->data);
    free(last);
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

    int len = listLength();

    if (pos < 1 || pos > len) {
        printf("Invalid position.\n");
        return;
    }

    if (pos == 1) {
        deleteBeginning();
        return;
    }

    struct Node *temp = head;
    for (int i = 1; i < pos; i++) {
        temp = temp->next;
    }

    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;

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
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);
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
        printf("\n----- CIRCULAR DOUBLY LINKED LIST OPERATIONS MENU -----\n");
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