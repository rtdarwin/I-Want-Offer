#include <stdio.h>

#define INT_ARR_LEN(x) sizeof(x) / sizeof(int)

// ================================================================================

// return 1 if found
//        0 if not found
//       -1 if input invalid

int
find_one_duplicate(int arr[], int len, int* dup)
{
    if (arr == NULL || len <= 0 || dup == NULL)
        return -1;

    for (int i = 0; i < len; i++) {
        while (arr[i] != i) {
            if (arr[i] == arr[arr[i]]) {
                *dup = arr[i];
                return 1;
            }

            int temp = arr[i];
            arr[i] = arr[temp];
            arr[temp] = temp;

            printf("i=%d: ", i);
            for (int i = 0; i < len; i++) {
                printf("%d ", arr[i]);
            }
            printf("\n");
        }
    }

    // if not found
    return 0;
}

// ================================================================================

// return 0 if added success
//       -1 if `dup_arr' are full

static int
dup_once(int (*dup_arr)[2], int dup_arr_len, int dup)
{
    for (int i = 0; i < dup_arr_len; i++) {
        if (dup_arr[i][0] == -1) {
            dup_arr[i][0] = dup;
            dup_arr[i][1] = 2;
            return 0;
        } else if (dup_arr[i][0] == dup) {
            ++dup_arr[i][1];
            return dup_arr[i][1];
        }
    }

    // if dup_arr are full
    return -1;
}


// return 1 if found duplicated digits
//        0 if number of duplicated digits are more that the dup_arr_len
//       -1 if input invalid

int
find_all_duplicate(int arr[], int len, int (*dup_arr)[2], int dup_arr_len)
{
    if (arr == NULL || dup_arr == NULL || len <= 0 || dup_arr_len <= 0)
        return -1;

    for (int i = 0; i < len; i++) {
        while (arr[i] != i) {
            // -1 时:
            //  a) 自己的数字与别人的一样, 这个位置的数字被抹掉了
            //  b) 自己把自己该处的位置的 -1 替换过来了,
            //     此时保证自己的数字处于应该的位置上,
            //     用于后续比较
            if (arr[i] == -1)
                break;

            if (arr[i] == arr[arr[i]]) {
                // if full
                if (dup_once(dup_arr, dup_arr_len, arr[i]) == -1) {
                    return 1;
                }

                // 抹掉这个位置
                arr[i] = -1;
            } else {
                int temp = arr[i];
                arr[i] = arr[temp];
                arr[temp] = temp;
            }

            printf("i=%d: ", i);
            for (int i = 0; i < len; i++) {
                printf("%d ", arr[i]);
            }
            printf("\n");
        }
    }

    return 0;
}

// ================================================================================

int
const_find_one_duplicate(const int* arr, int len)
{
    // it doesn't work
}

// ================================================================================

int
main()
{
    int arr[] = { 3, 4, 5, 4, 3, 0, 0 };
    /* int arr[] = { 3, 1, 2, 0, 2, 5, 3 }; */

    int dup;
    if (find_one_duplicate(arr, INT_ARR_LEN(arr), &dup) == 1) {
        printf("one dup: %d\n\n", dup);
    }

    // assume max 3
    int all_dup[3][2] = { { -1 }, { -1 }, { -1 } };
    find_all_duplicate(arr, INT_ARR_LEN(arr), all_dup,
                       sizeof(all_dup) / sizeof(int[2]));
    printf("all dup:\n");
    for (int i = 0; i < 3; i++) {
        printf("  %d  %d times\n", all_dup[i][0], all_dup[i][1]);
    }

    return 0;
}
