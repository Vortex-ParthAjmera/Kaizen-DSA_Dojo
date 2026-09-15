/*
    DSA Practical 6: Stack Operations using Array
    Operations: Push, Pop, Peek, isFull, isEmpty
    ----------------------------------------------------
    Compile : gcc stack_array_operations.c -o stack_array_operations
    Run     : ./stack_array_operations
*/

#include <stdio.h>

#define MAX 5          // maximum size of the stack

int s[MAX];            // stack array
int top = -1;          // top index (-1 means stack is empty)

// -------------------- isEMPTY --------------------
int isEmpty() {
    if (top == -1)
        return 1;      // true
    else
        return 0;      // false
}

// -------------------- isFULL --------------------
int isFull() {
    if (top == MAX - 1)
        return 1;      // true
    else
        return 0;      // false
}

// -------------------- PUSH --------------------
void push() {
    int v;

    if (isFull()) {
        printf("Stack Overflow. Cannot push.\n");
        return;
    }

    printf("Enter value to push: ");
    scanf("%d", &v);

    top++;
    s[top] = v;

    printf("%d pushed onto stack.\n", v);
}

// -------------------- POP --------------------
void pop() {
    if (isEmpty()) {
        printf("Stack Underflow. Cannot pop.\n");
        return;
    }

    printf("%d popped from stack.\n", s[top]);
    top--;
}

// -------------------- PEEK --------------------
void peek() {
    if (isEmpty()) {
        printf("Stack is empty. No top element.\n");
        return;
    }

    printf("Top element is %d.\n", s[top]);
}

// -------------------- DISPLAY --------------------
void display() {
    if (isEmpty()) {
        printf("Stack is empty.\n");
        return;
    }

    printf("Stack elements (top to bottom): ");
    for (int i = top; i >= 0; i--) {
        printf("%d ", s[i]);
    }
    printf("\n");
}

// -------------------- MAIN MENU --------------------
int main() {
    int ch;

    do {
        printf("\n----- STACK OPERATIONS MENU -----\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. isFull\n");
        printf("5. isEmpty\n");
        printf("6. Display\n");
        printf("7. Exit\n");
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
                if (isFull())
                    printf("Stack is FULL.\n");
                else
                    printf("Stack is NOT full.\n");
                break;
            case 5:
                if (isEmpty())
                    printf("Stack is EMPTY.\n");
                else
                    printf("Stack is NOT empty.\n");
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