#include <stdio.h>
#include <stdlib.h>

void
mergeSortedArr(int* arr1, int len1, int capacity, const int* arr2, int len2)
{
    if (len1 + len2 > capacity)
        return;

    int i = len1 - 1;
    int j = len2 - 1;
    int k = len1 + len2 - 1;
    while (i >= 0 && j >= 0) {
        if (arr1[i] > arr2[j]) {
            arr1[k] = arr1[i];
            --k, --i;
        } else {
            arr1[k] = arr2[j];
            --k, --j;
        }
    }

    while (j >= 0) {
        arr1[k--] = arr2[j--];
    }
}

int
main()
{
    int arr1[100] = { 1, 4, 5, 6, 7 };
    int arr2[5] = { 0, 2, 3, 8, 9 };
    mergeSortedArr(arr1, 5, 100, arr2, 5);

    for (int i = 0; i < 10; i++) {
        printf("%d ", arr1[i]);
    }
    fputc('\n', stdout);

    return 0;
}
