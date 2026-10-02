/*
    DSA Practical 13: Balanced Parentheses Checking using Stack
    ----------------------------------------------------
    Compile : gcc balanced_parentheses.c -o balanced_parentheses
    Run     : ./balanced_parentheses
*/

#include <stdio.h>

#define MAX 100
char s[MAX];
int top = -1;

void push(char c) { s[++top] = c; }
char pop() { return s[top--]; }
int isEmptyStack() { return top == -1; }

int isMatch(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

int main() {
    char e[MAX];
    printf("Enter expression: ");
    scanf("%s", e);

    int balanced = 1;

    for (int i = 0; e[i] != '\0'; i++) {
        char c = e[i];

        if (c == '(' || c == '{' || c == '[') {
            push(c);
        }
        else if (c == ')' || c == '}' || c == ']') {
            if (isEmptyStack() || !isMatch(pop(), c)) {
                balanced = 0;
                break;
            }
        }
    }

    if (!isEmptyStack()) balanced = 0;

    if (balanced)
        printf("Balanced\n");
    else
        printf("Not Balanced\n");

    return 0;
}