/*
    DSA Practical 7: Stack Operations using Linked List
    Operations: Push, Pop, Peek, isEmpty
    (No isFull here - a linked list stack grows dynamically,
     it only runs out of memory, not out of "slots")
    ----------------------------------------------------
    Compile : gcc stack_linked_list_operations.c -o stack_linked_list_operations
    Run     : ./stack_linked_list_operations
*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int d;          // data
    struct Node *n; // next
};

struct Node *top = NULL;   // top of stack

// -------------------- isEMPTY --------------------
int isEmpty() {
    if (top == NULL)
        return 1;      // true
    else
        return 0;      // false
}

// -------------------- PUSH --------------------
void push() {
    int v;
    printf("Enter value to push: ");
    scanf("%d", &v);

    struct Node *nn = (struct Node *)malloc(sizeof(struct Node));
    nn->d = v;
    nn->n = top;
    top = nn;

    printf("%d pushed onto stack.\n", v);
}

// -------------------- POP --------------------
void pop() {
    if (isEmpty()) {
        printf("Stack Underflow. Cannot pop.\n");
        return;
    }

    struct Node *t = top;
    printf("%d popped from stack.\n", t->d);
    top = top->n;
    free(t);
}

// -------------------- PEEK --------------------
void peek() {
    if (isEmpty()) {
        printf("Stack is empty. No top element.\n");
        return;
    }

    printf("Top element is %d.\n", top->d);
}

// -------------------- DISPLAY --------------------
void display() {
    if (isEmpty()) {
        printf("Stack is empty.\n");
        return;
    }

    struct Node *t = top;
    printf("Stack elements (top to bottom): ");
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
        printf("\n----- STACK (LINKED LIST) OPERATIONS MENU -----\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. isEmpty\n");
        printf("5. Display\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                push();
                break;
            case 2:
                pop();
                break;
            case 3:
                peek();
                break;
            case 4:
                if (isEmpty())
                    printf("Stack is EMPTY.\n");
                else
                    printf("Stack is NOT empty.\n");
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