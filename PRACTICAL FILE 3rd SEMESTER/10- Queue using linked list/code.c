/*
    DSA Practical 10: Queue Operations using Linked List
    Operations: Enqueue, Dequeue, Peek, isEmpty
    (No isFull here - a linked list queue grows dynamically)
    ----------------------------------------------------
    Compile : gcc queue_linked_list_operations.c -o queue_linked_list_operations
    Run     : ./queue_linked_list_operations
*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int d;          // data
    struct Node *n; // next
};

struct Node *front = NULL;   // front of queue
struct Node *rear = NULL;    // rear of queue

// -------------------- isEMPTY --------------------
int isEmpty() {
    if (front == NULL)
        return 1;      // true
    else
        return 0;      // false
}

// -------------------- ENQUEUE --------------------
void enqueue() {
    int v;
    printf("Enter value to enqueue: ");
    scanf("%d", &v);

    struct Node *nn = (struct Node *)malloc(sizeof(struct Node));
    nn->d = v;
    nn->n = NULL;

    if (front == NULL) {
        front = nn;
        rear = nn;
    } else {
        rear->n = nn;
        rear = nn;
    }

    printf("%d enqueued into queue.\n", v);
}

// -------------------- DEQUEUE --------------------
void dequeue() {
    if (isEmpty()) {
        printf("Queue Underflow. Cannot dequeue.\n");
        return;
    }

    struct Node *t = front;
    printf("%d dequeued from queue.\n", t->d);

    front = front->n;
    if (front == NULL) {
        rear = NULL;   // queue is now empty
    }

    free(t);
}

// -------------------- PEEK --------------------
void peek() {
    if (isEmpty()) {
        printf("Queue is empty. No front element.\n");
        return;
    }

    printf("Front element is %d.\n", front->d);
}

// -------------------- DISPLAY --------------------
void display() {
    if (isEmpty()) {
        printf("Queue is empty.\n");
        return;
    }

    struct Node *t = front;
    printf("Queue elements (front to rear): ");
    while (t != NULL) {
        printf("%d ", t->d);
        t = t->n;
    }
    printf("\n");
}

// -------------------- MAIN MENU --------------------
int main() {
    int ch;

    do {
        printf("\n----- QUEUE (LINKED LIST) OPERATIONS MENU -----\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. isEmpty\n");
        printf("5. Display\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                enqueue();
                break;
            case 2:
                dequeue();
                break;
            case 3:
                peek();
                break;
            case 4:
                if (isEmpty())
                    printf("Queue is EMPTY.\n");
                else
                    printf("Queue is NOT empty.\n");
                break;
            case 5:
                display();
                break;
            case 6:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (ch != 6);

    return 0;
}