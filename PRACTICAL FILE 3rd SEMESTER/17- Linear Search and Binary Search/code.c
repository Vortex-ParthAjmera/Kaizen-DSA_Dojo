/*
    DSA Practical 17: Linear Search and Binary Search
    ----------------------------------------------------
    Compile : gcc searching.c -o searching
    Run     : ./searching
*/

#include <stdio.h>

int linearSearch(int a[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (a[i] == key) return i;
    }
    return -1;
}

int binarySearch(int a[], int n, int key) {
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (a[mid] == key) return mid;
        else if (a[mid] < key) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

int main() {
    int a[100], b[100], n, key, pos;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }

    printf("Enter key to search: ");
    scanf("%d", &key);

    pos = linearSearch(a, n, key);
    if (pos != -1)
        printf("Linear Search: Found at index %d\n", pos);
    else
        printf("Linear Search: Not found\n");

    // binary search needs a sorted array - sort a copy
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (b[j] > b[j + 1]) {
                int t = b[j]; b[j] = b[j + 1]; b[j + 1] = t;
            }
        }
    }

    pos = binarySearch(b, n, key);
    if (pos != -1)
        printf("Binary Search: Found at index %d (in sorted array)\n", pos);
    else
        printf("Binary Search: Not found\n");

    return 0;
}