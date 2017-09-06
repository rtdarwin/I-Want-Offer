#include <stdio.h>
#include <stdlib.h>

void
swap(int* l, int* r)
{
    int t = *l;
    *l = *r;
    *r = t;
}

// [lo, hi]
void quickSortAux(int* arr, int lo, int hi);

int partition(int* arr, int lo, int hi);

// ascendingly sort arr
// return 1 if function sort the `arr' successfully
//        0 if the arr has already sorted
//       -1 if paramaters error
int
quickSort(int* arr, int len)
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

    /*  2. 开始快速排序
     *     c(T) = O(nlgn)
     *     c(S) = O(1)
     */

    // FIXME: shuffle `arr'

    // 最大元素移到最右边作为『哨兵』
    int maxIdx = 0;
    for (int i = 0; i < len; i++) {
        if (arr[i] > arr[maxIdx])
            maxIdx = i;
    }
    swap(arr + len - 1, arr + maxIdx);

    quickSortAux(arr, 0, len - 1);
    return 1;
}

void
quickSortAux(int* arr, int lo, int hi)
{
    // 触底情况
    if (lo == hi)
        return;

    int j = partition(arr, lo, hi);
    if (j >= lo + 2) {
        quickSortAux(arr, lo, j - 1);
    }
    if (hi >= j + 2) {
        quickSortAux(arr, j + 1, hi);
    }
}

int
partition(int* arr, int lo, int hi)
{
    fputc('\n', stdout);
    for (int i = 0; i < 14; i++) {
        printf("%d ", arr[i]);
    }
    fputc('\n', stdout);

    int i = lo, j = hi + 1;
    int v = arr[lo];
    printf("lo, hi, v = %d, %d, %d\n", lo, hi, v);

    for (;;) {
        // 注意，此处是 < 而不是 <=,
        //   因为我们子数组最后一个元素是『哨兵』，
        //   这个值通过以下措施保证了肯定『不小于』子数组中任意一个数字：
        //       - 开始排序前将最大元素移动到了原数组最右边
        //       - 每次 partition 之后，每个子数组最后一个元素的右边元素
        //         不小于此子数组中任意一个元素
        //    我们保证的是『不小于』，那么为了使 i 递增停下，
        //    停下的条件必须是『大于等于』。
        //    若 while 条件带等号，会使得停下的条件是『大于』
        //    这样，i 可能会越过哨兵
        //
        //  arr[--j] > v 中的 > 同理
        while (arr[++i] < v)
            ;
        while (arr[--j] > v)
            ;

        if (i >= j)
            break;
        swap(arr + i, arr + j);
    }
    printf("i, j = %d, %d\n", i, j);

    swap(arr + lo, arr + j);
    return j;
}

int
main()
{
    int arr[] = { 9, 8, 7, 5, 6, 5, 9, 4, 0, 8, 2, 4, 3, 0 };
    quickSort(arr, 14);

    for (int i = 0; i < 14; i++) {
        printf("%d ", arr[i]);
    }
    fputc('\n', stdout);

    return 0;
}
