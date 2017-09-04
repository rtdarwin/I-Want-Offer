#include <stdio.h>

void
swap(int* l, int* r)
{
    int t = *l;
    *l = *r;
    *r = t;
}

// ascedingly sort arr
// return 1 if function sort the `arr' successfully
//        0 if the arr has already sorted
//       -1 if paramaters error

int
selectionSort(int* arr, int len)
{
    if (arr == NULL || len == 0) {
        return -1;
    }

    /*  1. 如果已经排序了，直接返回
     *     c(T) = O(n)
     *     c(S) = O(1)
     */

    int sorted = 1;
    for (int i = 1; i < len; i++) {
        if (arr[i] < arr[i - 1]) {
            sorted = 0;
            break;
        }
    }
    if (sorted)
        return 0;

    /*  2. 开始选择排序
     *     c(T) = O(n^2)
     *     c(S) = O(1)
     */

    for (int i = 0; i < len; i++) {
        int minDigitIdx = i;
        for (int j = i; j < len; j++) {
            if (arr[j] < arr[minDigitIdx])
                minDigitIdx = j;
        }
        // 如果考虑分支对流水线处理器的影响，
        // 此处不进行判断可能会更好？
        if (minDigitIdx != i) {
            swap(arr + i, arr + minDigitIdx);
        }
    }

    return 1;
}

int
main()
{
    int arr[] = { 9, 8, 7, 6, 5, 4, 1, 2, 3, 0 };
    selectionSort(arr, 10);

    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    fputc('\n', stdout);

    return 0;
}
