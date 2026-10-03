/*
    DSA Practical 14: Deque (Double-Ended Queue) using Array
    Operations: Insert Front, Insert Rear, Delete Front,
                Delete Rear, isFull, isEmpty
    ----------------------------------------------------
    Compile : gcc deque_operations.c -o deque_operations
    Run     : ./deque_operations
*/

#include <stdio.h>

#define MAX 5
int q[MAX];
int front = -1, rear = -1;

int isEmpty() { return front == -1; }
int isFull()  { return (rear + 1) % MAX == front; }

void insertFront() {
    int v;
    if (isFull()) { printf("Deque Overflow.\n"); return; }
    printf("Enter value: ");
    scanf("%d", &v);

    if (front == -1) {
        front = rear = 0;
    } else {
        front = (front - 1 + MAX) % MAX;
    }
    q[front] = v;
    printf("%d inserted at front.\n", v);
}

void insertRear() {
    int v;
    if (isFull()) { printf("Deque Overflow.\n"); return; }
    printf("Enter value: ");
    scanf("%d", &v);

    if (front == -1) {
        front = rear = 0;
    } else {
        rear = (rear + 1) % MAX;
    }
    q[rear] = v;
    printf("%d inserted at rear.\n", v);
}

void deleteFront() {
    if (isEmpty()) { printf("Deque Underflow.\n"); return; }
    printf("%d deleted from front.\n", q[front]);
    if (front == rear) {
        front = rear = -1;
    } else {
        front = (front + 1) % MAX;
    }
}

void deleteRear() {
    if (isEmpty()) { printf("Deque Underflow.\n"); return; }
    printf("%d deleted from rear.\n", q[rear]);
    if (front == rear) {
        front = rear = -1;
    } else {
        rear = (rear - 1 + MAX) % MAX;
    }
}

void display() {
    if (isEmpty()) { printf("Deque is empty.\n"); return; }
    int cnt = (rear - front + MAX) % MAX + 1;
    printf("Deque elements (front to rear): ");
    for (int i = 0; i < cnt; i++) {
        printf("%d ", q[(front + i) % MAX]);
    }
    printf("\n");
}

int main() {
    int ch;
    do {
        printf("\n----- DEQUE OPERATIONS MENU -----\n");
        printf("1. Insert at Front\n");
        printf("2. Insert at Rear\n");
        printf("3. Delete from Front\n");
        printf("4. Delete from Rear\n");
        printf("5. isFull\n");
        printf("6. isEmpty\n");
        printf("7. Display\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: insertFront(); break;
            case 2: insertRear(); break;
            case 3: deleteFront(); break;
            case 4: deleteRear(); break;
            case 5:
                if (isFull()) printf("Deque is FULL.\n");
                else printf("Deque is NOT full.\n");
                break;
            case 6:
                if (isEmpty()) printf("Deque is EMPTY.\n");
                else printf("Deque is NOT empty.\n");
                break;
            case 7: display(); break;
            case 8: printf("Exiting program.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (ch != 8);

    return 0;
}