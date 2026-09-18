/*
    DSA Practical 8: Queue Operations using Array
    Operations: Enqueue, Dequeue, Peek, isFull, isEmpty
    ----------------------------------------------------
    Compile : gcc queue_array_operations.c -o queue_array_operations
    Run     : ./queue_array_operations
*/

#include <stdio.h>

#define MAX 5          // maximum size of the queue

int q[MAX];            // queue array
int front = -1;        // front index (-1 means queue is empty)
int rear = -1;         // rear index

// -------------------- isEMPTY --------------------
int isEmpty() {
    if (front == -1)
        return 1;      // true
    else
        return 0;      // false
}

// -------------------- isFULL --------------------
int isFull() {
    if (rear == MAX - 1)
        return 1;      // true
    else
        return 0;      // false
}

// -------------------- ENQUEUE --------------------
void enqueue() {
    int v;

    if (isFull()) {
        printf("Queue Overflow. Cannot enqueue.\n");
        return;
    }

    printf("Enter value to enqueue: ");
    scanf("%d", &v);

    if (front == -1) {
        front = 0;
    }
    rear++;
    q[rear] = v;

    printf("%d enqueued into queue.\n", v);
}

// -------------------- DEQUEUE --------------------
void dequeue() {
    if (isEmpty()) {
        printf("Queue Underflow. Cannot dequeue.\n");
        return;
    }

    printf("%d dequeued from queue.\n", q[front]);

    if (front == rear) {
        // last element was just removed
        front = -1;
        rear = -1;
    } else {
        front++;
    }
}

// -------------------- PEEK --------------------
void peek() {
    if (isEmpty()) {
        printf("Queue is empty. No front element.\n");
        return;
    }

    printf("Front element is %d.\n", q[front]);
}

// -------------------- DISPLAY --------------------
void display() {
    if (isEmpty()) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue elements (front to rear): ");
    for (int i = front; i <= rear; i++) {
        printf("%d ", q[i]);
    }
    printf("\n");
}

// -------------------- MAIN MENU --------------------
int main() {
    int ch;

    do {
        printf("\n----- QUEUE OPERATIONS MENU -----\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. isFull\n");
        printf("5. isEmpty\n");
        printf("6. Display\n");
        printf("7. Exit\n");
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
                if (isFull())
                    printf("Queue is FULL.\n");
                else
                    printf("Queue is NOT full.\n");
                break;
            case 5:
                if (isEmpty())
                    printf("Queue is EMPTY.\n");
                else
                    printf("Queue is NOT empty.\n");
                break;
            case 6:
                display();
                break;
            case 7:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (ch != 7);

    return 0;
}