/*
    DSA Practical 1: Array Operations
    Implements: Traverse, Insert, Delete
    ----------------------------------------------------
    Compile : gcc array_operations.c -o array_operations
    Run     : ./array_operations
*/

#include <stdio.h>

#define MAX 100   // maximum capacity of the array

int arr[MAX];
int n = 0;        // current number of elements in the array

// -------------------- TRAVERSE --------------------
void traverse() {
    if (n == 0) {
        printf("Array is empty.\n");
        return;
    }
    printf("Array elements: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// -------------------- INSERT --------------------
void insert() {
    int value, pos;

    if (n == MAX) {
        printf("Array is full. Cannot insert.\n");
        return;
    }

    printf("Enter value to insert: ");
    scanf("%d", &value);

    printf("Enter position (1 to %d): ", n + 1);
    scanf("%d", &pos);

    if (pos < 1 || pos > n + 1) {
        printf("Invalid position.\n");
        return;
    }

    // Shift elements to the right to make space
    for (int i = n; i >= pos; i--) {
        arr[i] = arr[i - 1];
    }

    arr[pos - 1] = value;
    n++;

    printf("Value %d inserted at position %d.\n", value, pos);
}

// -------------------- DELETE --------------------
void deleteElement() {
    int pos;

    if (n == 0) {
        printf("Array is empty. Nothing to delete.\n");
        return;
    }

    printf("Enter position to delete (1 to %d): ", n);
    scanf("%d", &pos);

    if (pos < 1 || pos > n) {
        printf("Invalid position.\n");
        return;
    }

    int deletedValue = arr[pos - 1];

    // Shift elements to the left to fill the gap
    for (int i = pos - 1; i < n - 1; i++) {
        arr[i] = arr[i + 1];
    }

    n--;

    printf("Value %d deleted from position %d.\n", deletedValue, pos);
}

// -------------------- MAIN MENU --------------------
int main() {
    int choice;

    // ---- take initial size and elements from the user ----
    printf("Enter initial number of elements (0 to %d): ", MAX);
    scanf("%d", &n);

    if (n < 0 || n > MAX) {
        printf("Invalid size. Setting array as empty.\n");
        n = 0;
    } else {
        for (int i = 0; i < n; i++) {
            printf("Enter element %d: ", i + 1);
            scanf("%d", &arr[i]);
        }
    }

    do {
        printf("\n----- ARRAY OPERATIONS MENU -----\n");
        printf("1. Traverse\n");
        printf("2. Insert\n");
        printf("3. Delete\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                traverse();
                break;
            case 2:
                insert();
                break;
            case 3:
                deleteElement();
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 4);

    return 0;
}