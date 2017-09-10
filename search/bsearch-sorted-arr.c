#include <stdio.h>
#include <stdlib.h>

// return the location of value
//        -1 if not found
// [begin, end)
int
bisearch(const int* arr, int begin, int end, int value)
{
    if (arr == NULL || begin == end)
        return -1;

    // [lo, hi]
    int lo = begin;
    int hi = end - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;

        // 找到了就直接返回
        if (arr[mid] == value)
            return mid;

        // 确定下一步找左边还是右边
        if (arr[mid] > value)
            hi = mid - 1;
        else
            lo = mid + 1;
    }

    return -1;
}

int
main()
{
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
    int toFind = 9;
    int loc = bisearch(arr, 0, sizeof(arr) / sizeof(int), toFind);
    if (loc != -1) {
        printf("find value %1$d in location %2$d\narr[%2$d] = %3$d\n", toFind,
               loc, arr[loc]);
    }
    return 0;
}
