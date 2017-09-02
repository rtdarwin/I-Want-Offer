#include <stdio.h>

void
replaceSpaceInStr(char* str, int capacity)
{
    int origLen = 0, resultLen = 0;

    /*  1. calculate length */

    const char* pStr = str;
    while (*pStr != '\0') {
        if (*pStr == ' ') {
            resultLen += 3;
        } else {
            resultLen += 1;
        }

        pStr++;
    }

    origLen = pStr - str;

    if (resultLen > capacity)
        return;

    /*  2. substitude */

    int i = origLen - 1;
    int j = resultLen - 1;
    str[resultLen] = '\0';

    while (i >= 0) {
        if (str[i] == ' ') {
            str[j--] = '0';
            str[j--] = '2';
            str[j--] = '%';
        } else {
            str[j--] = str[i];
        }
        --i;
    }
}

int
main()
{

    char strs[4][100] = { "hey", "i'm robert ", " ", "nice to meet you ." };

    for (int i = 0; i < 4; i++) {
        printf("\"%s\"\n", strs[i]);
        replaceSpaceInStr(strs[i], 100);
        printf("\"%s\"\n", strs[i]);
    }

    return 0;
}
