#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "common_threads.h"
#include "smoker.h"

void smoker_init(smoker_t *sp) {
    Sem_init(&sp->agent, 0, 1);
    Sem_init(&sp->all_smoker, 0, 1);

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
        V(&sp->tobacco); // Tell tobacco to smoke
        break;
    case 1:
        printf("Agent places tobacco and match\n");
        V(&sp->paper); // Tell paper to smoke
        break;
    case 2:
        printf("Agent places paper and tobacco\n");
        V(&sp->match); // Tell match to smoke
        break;
    default:
        break;
    }
    sleep(0.5);
    P(&sp->agent); // prevent agent to put more than 2 thing on table
}

int smoker_remove(smoker_t *sp, char *msg) {
    switch (msg[0]) {
    case 'T':
        P(&sp->tobacco);
        P(&sp->all_smoker);
        printf("Tobacco smoker smokes\n");
        sleep(1);
        V(&sp->all_smoker);
        V(&sp->agent);
        break;
    case 'P':
        P(&sp->paper);
        P(&sp->all_smoker);
        printf("Paper smoker smokes\n");
        sleep(1);
        V(&sp->all_smoker);
        V(&sp->agent);
        break;
    case 'M':
        P(&sp->match);
        P(&sp->all_smoker);
        printf("Match smoker smokes\n");
        sleep(1);
        V(&sp->all_smoker);
        V(&sp->agent);
        break;
    default:
        break;
    }
}
