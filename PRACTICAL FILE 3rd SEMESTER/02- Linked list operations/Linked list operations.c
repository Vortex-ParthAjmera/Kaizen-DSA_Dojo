#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *head = NULL;

void insertBeginningHelper(int value);   // forward declaration
void insertEndValue(int value);          // forward declaration

// -------------------- INSERT AT BEGINNING --------------------
void insertBeginning() {
    int value;
    printf("Enter value to insert: ");
    scanf("%d", &value);

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = head;
    head = newNode;

    printf("%d inserted at beginning.\n", value);
}

// -------------------- INSERT AT END --------------------
void insertEndValue(int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        struct Node *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
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
    int value, pos, count = 1;
    printf("Enter value to insert: ");
    scanf("%d", &value);
    printf("Enter position to insert at: ");
    scanf("%d", &pos);

    if (pos == 1) {
        insertBeginningHelper(value);
        return;
    }

    struct Node *temp = head;
    for (int i = 1; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
        count++;
    }

    if (temp == NULL) {
        printf("Invalid position.\n");
        return;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = temp->next;
    temp->next = newNode;

    printf("%d inserted at position %d.\n", value, pos);
}

// helper used by insertMiddle when position is 1
void insertBeginningHelper(int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = head;
    head = newNode;
    printf("%d inserted at position 1.\n", value);
}

// -------------------- DELETE AT BEGINNING --------------------
void deleteBeginning() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node *temp = head;
    head = head->next;
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
    while (temp->next->next != NULL) {
        temp = temp->next;
    }

    printf("%d deleted from end.\n", temp->next->data);
    free(temp->next);
    temp->next = NULL;
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
    for (int i = 1; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) {
        printf("Invalid position.\n");
        return;
    }

    struct Node *toDelete = temp->next;
    temp->next = toDelete->next;
    printf("%d deleted from position %d.\n", toDelete->data, pos);
    free(toDelete);
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
        printf("\n----- LINKED LIST OPERATIONS MENU -----\n");
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
            case 1:
                insertBeginning();
                break;
            case 2:
                insertMiddle();
                break;
            case 3:
                insertEnd();
                break;
            case 4:
                deleteBeginning();
                break;
            case 5:
                deleteMiddle();
                break;
            case 6:
                deleteEnd();
                break;
            case 7:
                display();
                break;
            case 8:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 8);

    return 0;
}