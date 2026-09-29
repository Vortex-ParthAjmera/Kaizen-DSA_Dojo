/*
    DSA Practical 12: Postfix Expression Evaluation using Stack
    ----------------------------------------------------
    Compile : gcc postfix_evaluation.c -o postfix_evaluation
    Run     : ./postfix_evaluation
    Note    : Enter single-digit operands only, e.g. 23*54*+9-
*/

#include <stdio.h>
#include <ctype.h>

#define MAX 100
int s[MAX];
int top = -1;

void push(int v) { s[++top] = v; }
int pop() { return s[top--]; }

int main() {
    char e[MAX];
    printf("Enter postfix expression: ");
    scanf("%s", e);

    for (int i = 0; e[i] != '\0'; i++) {
        char c = e[i];

        if (isdigit(c)) {
            push(c - '0');
        } else {
            int b = pop();
            int a = pop();
            int r;
            switch (c) {
                case '+': r = a + b; break;
                case '-': r = a - b; break;
                case '*': r = a * b; break;
                case '/': r = a / b; break;
                default:  r = 0;
            }
            push(r);
        }
    }

    printf("Result = %d\n", pop());
    return 0;
}