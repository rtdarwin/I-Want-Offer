#include <stdio.h>
#include <stdlib.h>

void
swap(int* l, int* r)
{
    int t = *l;
    *l = *r;
    *r = t;
}

// 每一次 merge 都需要额外的存储空间，所以此处统一一下都使用
//   aux_arr, 避免每次 merge 都重分配空间，影响速度
int* aux_arr = NULL;

// [lo, mid], [mid+1, hi]
void mergeSortAux(int* arr, int lo, int hi);
void merge(int* arr, int lo, int mid, int hi);

// ascedingly sort arr
// return 1 if function sort the `arr' successfully
//        0 if the arr has already sorted
//       -1 if paramaters error
int
mergeSort(int* arr, int len)
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

    /*  2. 开始归并排序
     *     c(T) = O(nlgn)
     *     c(S) = O(n)
     */

    aux_arr = (int*)malloc(sizeof(int) * len);
    mergeSortAux(arr, 0, len - 1);

    return 1;
}

void
mergeSortAux(int* arr, int lo, int hi)
{
    if (lo == hi)
        return;

    int mid = lo + (hi - lo) / 2;
    mergeSortAux(arr, lo, mid);
    mergeSortAux(arr, mid + 1, hi);
    merge(arr, lo, mid, hi);
}

void
merge(int* arr, int lo, int mid, int hi)
{
    int i = lo;
    int j = mid + 1;

    int k;
    for (k = lo; k <= hi; k++) {
        aux_arr[k] = arr[k];
    }

    for (k = lo; k <= hi; k++) {
        if (i > mid) {
            arr[k] = aux_arr[j++];
        } else if (j > hi) {
            arr[k] = aux_arr[i++];
        } else if (aux_arr[i] < aux_arr[j]) {
            arr[k] = aux_arr[i++];
        } else {
            arr[k] = aux_arr[j++];
        }
    }
}

int
main()
{
    int arr[] = { 9, 8, 7, 6, 5, 4, 1, 2, 3, 0 };
    mergeSort(arr, 10);

    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    fputc('\n', stdout);

    return 0;
}
