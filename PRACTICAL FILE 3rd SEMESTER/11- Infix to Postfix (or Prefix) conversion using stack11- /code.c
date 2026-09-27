/*
    DSA Practical 11: Infix to Postfix Conversion using Stack
    ----------------------------------------------------
    Compile : gcc infix_to_postfix.c -o infix_to_postfix
    Run     : ./infix_to_postfix
    Note    : Enter the expression with single-character
              operands and no spaces, e.g. (a+b)*c
*/

#include <stdio.h>
#include <ctype.h>

#define MAX 100

char s[MAX];     // stack for operators
int top = -1;

// -------------------- STACK HELPERS --------------------
void push(char c) {
    s[++top] = c;
}

char pop() {
    return s[top--];
}

char peekTop() {
    return s[top];
}

int isEmptyStack() {
    return top == -1;
}

// -------------------- PRECEDENCE --------------------
int prec(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return -1;           // for '(' or anything else
}

int isOp(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// -------------------- INFIX TO POSTFIX --------------------
void toPostfix(char *e, char *p) {
    int i, j = 0;

    for (i = 0; e[i] != '\0'; i++) {
        char c = e[i];

        if (isalnum(c)) {
            // operand: send straight to output
            p[j++] = c;
        }
        else if (c == '(') {
            push(c);
        }
        else if (c == ')') {
            while (!isEmptyStack() && peekTop() != '(') {
                p[j++] = pop();
            }
            pop();        // discard the '('
        }
        else if (isOp(c)) {
            while (!isEmptyStack() &&
                   (prec(peekTop()) > prec(c) ||
                    (prec(peekTop()) == prec(c) && c != '^'))) {
                p[j++] = pop();
            }
            push(c);
        }
    }

    while (!isEmptyStack()) {
        p[j++] = pop();
    }

    p[j] = '\0';
}

// -------------------- MAIN --------------------
int main() {
    char e[MAX], p[MAX];

    printf("Enter infix expression: ");
    scanf("%s", e);

    toPostfix(e, p);

    printf("Postfix expression: %s\n", p);

    return 0;
}