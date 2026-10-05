/*
    DSA Practical 16: Tower of Hanoi
    ----------------------------------------------------
    Compile : gcc tower_of_hanoi.c -o tower_of_hanoi
    Run     : ./tower_of_hanoi
*/

#include <stdio.h>

int cnt = 0;

void hanoi(int n, char from, char aux, char to) {
    if (n == 0) return;
    hanoi(n - 1, from, to, aux);
    printf("Move disk %d from %c to %c\n", n, from, to);
    cnt++;
    hanoi(n - 1, aux, from, to);
}

int main() {
    int n;
    printf("Enter number of disks: ");
    scanf("%d", &n);

    hanoi(n, 'A', 'B', 'C');

    printf("Total moves = %d\n", cnt);

    return 0;
}