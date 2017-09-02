#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int n;
char str[1024];

int print_turn = 0;
pthread_cond_t cond_print_turn = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mtx_print_turn = PTHREAD_MUTEX_INITIALIZER;

void*
print_thread(void* my_turn)
{
    long my_turn_idx = (long)my_turn;

    for (;;) {
        pthread_mutex_lock(&mtx_print_turn);
        while (print_turn != my_turn_idx)
            pthread_cond_wait(&cond_print_turn, &mtx_print_turn);

        putc(str[my_turn_idx], stdout);
        print_turn++;

        pthread_mutex_unlock(&mtx_print_turn);
        pthread_cond_broadcast(&cond_print_turn);
    }
}

int
main()
{
    scanf("%d %s", &n, str);
    int str_len = strlen(str);

    /* 1. 非主线程打印非终结字符 */

    pthread_t t;
    for (int i = 0; i < str_len - 1; i++) {
        pthread_create(&t, NULL, print_thread, (void*)(long)i);
    }

    /* 2. 主线程打印终结字符，控制进度 */

    int process = 0;
    while (process != n) {
        pthread_mutex_lock(&mtx_print_turn);
        while (print_turn != str_len - 1)
            pthread_cond_wait(&cond_print_turn, &mtx_print_turn);

        putc(str[str_len - 1], stdout);
        process++;
        if (process != n) {
            print_turn = 0;
        }

        pthread_mutex_unlock(&mtx_print_turn);
        pthread_cond_broadcast(&cond_print_turn);
    }

    return 0;
}
