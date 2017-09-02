#include <stdio.h>
#include <stdlib.h>

struct pair
{
    int first;
    int second;
};

/*  return 1 if found
 *         0 if not found
 */

int
findKInSortedMatrix(int (*matrix)[4], int nrow, int ncol, int k,
                    struct pair* pLoc)
{
    int predX = 0;
    int predY = ncol - 1;

    int found = 0;
    while (predX <= nrow && predY >= 0) {

#ifndef NDEBUG
        printf("(x,y) = (%d,%d)\n", predX, predY);
#endif

        int curr = matrix[predX][predY];
        if (curr == k) {
            found = 1;
            break;
        } else if (curr > k) {
            --predY;
        } else if (curr < k) {
            ++predX;
        }
    }

    if (found) {
        pLoc->first = predX;
        pLoc->second = predY;
        return 1;
    } else {
        return 0;
    }
}

int
main()
{
    int sortedMatrix[][4] = {
        { 1, 2, 8, 9 }, { 2, 4, 9, 12 }, { 4, 7, 10, 13 }, { 6, 8, 11, 15 }
    };
    int toFind = 7;

    struct pair loc;
    if (findKInSortedMatrix(sortedMatrix, 4, 4, toFind, &loc)) {
        printf("find %d in location (%d,%d)\n", toFind, loc.first, loc.second);
    } else {
        printf("not found\n");
    }

    return 0;
}
