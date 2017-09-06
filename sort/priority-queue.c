#include <stdio.h>

void
swap(int* l, int* r)
{
    int t = *l;
    *l = *r;
    *r = t;
}

struct HeapPriorityQueue
{
    int arr[100];
    int idx;
};

void
enPriorityQueue(struct HeapPriorityQueue* pq, int e)
{
    int loc = ++(pq->idx);
    pq->arr[loc] = e;

    // swim
    while (loc > 1 && e > pq->arr[loc / 2]) {
        swap(pq->arr + loc, pq->arr + loc / 2);
        loc /= 2;
    }
}

int
topOfPriorityQueue(struct HeapPriorityQueue* pq)
{
    if (pq->idx >= 1)
        return pq->arr[1];
    else
        return 0xffffffff;
}

void
dePriorityQueue(struct HeapPriorityQueue* pq)
{
    if (pq->idx < 1)
        return;

    pq->arr[1] = pq->arr[(pq->idx)--];

    // sink
    int loc = 1;
    while (2 * loc <= pq->idx) {
        int toXhgLoc = 2 * loc;
        
        // 右子节点
        if (toXhgLoc + 1 <= pq->idx &&
            pq->arr[toXhgLoc] < pq->arr[toXhgLoc + 1]) {
            toXhgLoc += 1;
        }

        // 如果这个节点比左右子节点都要大，sink 结束
        if(pq->arr[loc] >= pq->arr[toXhgLoc])
          break;
        
        swap(pq->arr + toXhgLoc, pq->arr + loc);
        loc = toXhgLoc;
    }

}

int
main()
{
    struct HeapPriorityQueue pq = {.idx = 0 };

    int a[] = { 9, 0, 7, 6, 11, 4, 1, 2, 3, 0 };
    for (int i = 0; i < 10; i++) {
        enPriorityQueue(&pq, a[i]);
    }

    for (int i = 0; i < 10; i++) {
        printf("%d ", topOfPriorityQueue(&pq));
        dePriorityQueue(&pq);
    }
    fputc('\n', stdout);

    return 0;
}
