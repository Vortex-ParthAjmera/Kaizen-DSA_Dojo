/*
    DSA Practical 15: Factorial, Fibonacci, GCD using Recursion
    ----------------------------------------------------
    Compile : gcc recursion_basics.c -o recursion_basics
    Run     : ./recursion_basics
*/

#include <stdio.h>

int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    int ch;

    do {
        printf("\n----- RECURSION MENU -----\n");
        printf("1. Factorial\n");
        printf("2. Fibonacci (first n terms)\n");
        printf("3. GCD\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        if (ch == 1) {
            int n;
            printf("Enter n: ");
            scanf("%d", &n);
            printf("Factorial of %d = %d\n", n, factorial(n));
        }
        else if (ch == 2) {
            int n;
            printf("Enter number of terms: ");
            scanf("%d", &n);
            printf("Fibonacci series: ");
            for (int i = 0; i < n; i++) {
                printf("%d ", fibonacci(i));
            }
            printf("\n");
        }
        else if (ch == 3) {
            int a, b;
            printf("Enter two numbers: ");
            scanf("%d %d", &a, &b);
            printf("GCD of %d and %d = %d\n", a, b, gcd(a, b));
        }
        else if (ch == 4) {
            printf("Exiting program.\n");
        }
        else {
            printf("Invalid choice.\n");
        }
    } while (ch != 4);

    return 0;
}