#include <stdio.h>

void
swap(int* l, int* r)
{
    int t = *l;
    *l = *r;
    *r = t;
}

// [1, last]
static void
sink(int* arr, int currIdx, int lastIdx)
{
    while (2 * currIdx <= lastIdx) {
        // 从左右字节点中选出最大的那个
        int toXhgLoc = currIdx * 2;
        if (toXhgLoc + 1 <= lastIdx && arr[toXhgLoc + 1] > arr[toXhgLoc])
            toXhgLoc += 1;

        if (arr[currIdx] > arr[toXhgLoc])
            break;
        swap(arr + currIdx, arr + toXhgLoc);
        currIdx = toXhgLoc;
    }
}

// ascendingly sort arr
// return 1 if function sort the `arr' successfully
//        0 if the arr has already sorted
//       -1 if paramaters error
int
heapSort(int* arr, int len)
{
    if (arr == NULL || len == 0)
        return -1;

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

    /*  2. 开始堆排序
     *     c(T) = O(nlgn)
     *     c(S) = O(1)
     *
     *   堆排序最容易处理的情况是 arr[0] 不使用，
     *   这个时候很容易使用完全二叉树的父子节点编号关系（2*i, 2*i+1）
     *   来确定其父/子节点位置。但现实情况中，arr[0] 很少会不使用，
     *   若考虑到 arr[0]，会使得代码中出现大量难以理解的 +1 -1 运算。
     *   所以，
     *   在这里，我们先排序 arr[1..len-1]，
     *   之后，再将 arr[0] 插入排序到已排好的 arr[1..len-1] 中,
     *   使 arr[0..len-1] 都有序
     */

    /*  2.1 arr[1..len-1] */

    for (int k = (len - 1) / 2; k >= 1; k--) {
        sink(arr, k, len - 1);
    }
    int n = len - 1;
    while (n > 1) {
        swap(arr + 1, arr + n);
        --n;
        sink(arr, 1, n);
    }

    /*  2.2 arr[0] */

    int v = arr[0];
    int i;
    for (i = 1; i < len; i++) {
        if (arr[i] < v)
            arr[i - 1] = arr[i];
        else
            break;
    }
    arr[i - 1] = v;

    return 1;
}
int
main()
{
    int arr[] = { 5, 8, 0, 6, 4, 4, 1, 2, 3, 0 };
    heapSort(arr, 10);

    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    fputc('\n', stdout);

    return 0;
}
