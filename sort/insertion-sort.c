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
insertionSort(int* arr, int len)
{
    if (arr == NULL || len == 0) {
        return -1;
    }

    /*  1. 插入排序不需要进行数组顺序预检查，因为这个算法对输入敏感，
     *     当输入的数组已经有序时，可以达到 O(n) 的时间效率
     */

    // Do nothing

    /*  2. 开始插入排序
     *     c(T) = O(n) ~ O(n^2)
     *     c(S) = O(1)
     */

    for (int i = 1; i < len; i++) {
        int curr = arr[i];
        int j;
        for (j = i - 1; j >= 0; j--) {
            if (arr[j] > curr) {
                arr[j + 1] = arr[j];
            } else {
                break;
            }
        }
        if (j != i - 1) {
            arr[j + 1] = curr;
        }
    }

    return 1;
}

int
main()
{
    int arr[] = { 9, 8, 7, 6, 5, 4, 1, 2, 3, 0 };
    insertionSort(arr, 10);

    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    fputc('\n', stdout);

    return 0;
}
