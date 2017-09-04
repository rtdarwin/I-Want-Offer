#include <stdio.h>

long
fabonacci(unsigned int n)
{
    int results[2] = { 0, 1 };
    if (n < 2) {
        return results[n];
    }

    long lhs = 0;
    long rhs = 1;
    long fabonacci_i = 0;
    for (unsigned i = 2; i <= n; i++) {
        fabonacci_i = lhs + rhs;
        lhs = rhs;
        rhs = fabonacci_i;
    }

    return fabonacci_i;
}

int
main()
{
    unsigned int n = 10;
    printf("fabonacci(%d) = %ld\n", n, fabonacci(n));
    return 0;
}
