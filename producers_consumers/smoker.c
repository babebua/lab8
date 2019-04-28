/* $begin sbufc */
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "common_threads.h"
#include "smoker.h"

void smoker_init(smoker_t *sp) {
    Sem_init(&sp->agent, 0, 1);
    Sem_init(&sp->share, 0, 1);

    Sem_init(&sp->tobacco, 0, 0);
    Sem_init(&sp->paper, 0, 0);
    Sem_init(&sp->match, 0, 0);
}
void smoker_deinit(smoker_t *sp) { free(sp); }
void smoker_insert(smoker_t *sp) {
    int item = rand() % 3;
    switch (item) {
    case 0:
        printf("Agent places paper and match\n");
        V(&sp->tobacco);
        break;
    case 1:
        printf("Agent places tobacco and match\n");
        V(&sp->paper);
        break;
    case 2:
        printf("Agent places tobacco and paper\n");
        V(&sp->match);
        break;
    default:
        break;
    }
    sleep(1);
    P(&sp->agent);
}
int smoker_remove(smoker_t *sp, char *msg) {
    switch (msg[0]) {
    case 'T':
        P(&sp->tobacco);
        P(&sp->share);
        printf("Tobacco smoker smokes\n");
        sleep(1);
        V(&sp->share);
        V(&sp->agent);
        break;
    case 'P':
        P(&sp->paper);
        P(&sp->share);
        printf("Paper smoker smokes\n");
        sleep(1);
        V(&sp->share);
        V(&sp->agent);
        break;
    case 'M':
        P(&sp->match);
        P(&sp->share);
        printf("Match smoker smokes\n");
        sleep(1);
        V(&sp->share);
        V(&sp->agent);
        break;
    default:
        break;
    }
}
