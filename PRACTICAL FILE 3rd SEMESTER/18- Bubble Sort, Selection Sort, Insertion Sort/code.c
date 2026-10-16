/*
    DSA Practical 18: Bubble Sort, Selection Sort, Insertion Sort
    ----------------------------------------------------
    Compile : gcc sorting_basics.c -o sorting_basics
    Run     : ./sorting_basics
*/

#include <stdio.h>

void bubbleSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (a[j] > a[j + 1]) {
                int t = a[j]; a[j] = a[j + 1]; a[j + 1] = t;
            }
}

void selectionSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[minIdx]) minIdx = j;
        int t = a[i]; a[i] = a[minIdx]; a[minIdx] = t;
    }
}

void insertionSort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

void display(int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int a[100], b[100], c[100], n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    for (int i = 0; i < n; i++) { b[i] = a[i]; c[i] = a[i]; }

    bubbleSort(a, n);
    printf("Bubble Sort   : "); display(a, n);

    selectionSort(b, n);
    printf("Selection Sort: "); display(b, n);

    insertionSort(c, n);
    printf("Insertion Sort: "); display(c, n);

    return 0;
}