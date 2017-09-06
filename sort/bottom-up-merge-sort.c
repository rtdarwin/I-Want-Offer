#include <stdio.h>
#include <stdlib.h>

// 每一次 merge 都需要额外的存储空间，所以此处统一一下都使用
//   aux_arr, 避免每次 merge 都重分配空间，影响速度
int* aux_arr = NULL;

// [lo, mid], [mid+1, hi]
void merge(int* arr, int lo, int mid, int hi);

// 自底向上的归并排序作用于『链表』型数据时不需要分配额外的空间，
//   空间复杂度降为 O(1)
//
// ascendingly sort arr
// return 1 if function sort the `arr' successfully
//        0 if the arr has already sorted
//       -1 if paramaters error
int
bottomUpMergeSort(int* arr, int len)
{
    if (arr == NULL || len == 0)
        return -1;

    /*  自底向上归并排序
     *    c(T) = O(nlgn)
     *    c(S) = O(n)
     *
     *  试验性的使用
     *    - 测试要合并的两子数组是否已经有序
     */

    aux_arr = (int*)malloc(sizeof(int) * len);

    for (int sz = 1; sz < len; sz *= 2) {
        // 最后那个不恰好是 sz 大小的块处理很巧妙啊
        for (int lo = 0; lo < len - sz; lo += sz + sz) {
            int hi = lo + sz + sz - 1;
            if (hi > len - 1)
                hi = len - 1;
            printf("lo, hi = %d, %d\n", lo, hi);
            if (!(arr[lo + sz - 1] <= arr[lo + sz]))
                merge(arr, lo, lo + sz - 1, hi);
        }
    }

    return 1;
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
    bottomUpMergeSort(arr, 10);

    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    fputc('\n', stdout);

    return 0;
}
