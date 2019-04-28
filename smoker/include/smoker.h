// FINISH

#ifndef __SMOKER_H__
#define __SMOKER_H__

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

/* $begin smokert */
typedef struct {
    sem_t all_smoker;
    sem_t agent;
    sem_t tobacco;
    sem_t paper;
    sem_t match;
} smoker_t;
/* $end smokert */

void smoker_init(smoker_t *sp);
void smoker_deinit(smoker_t *sp);
void smoker_insert(smoker_t *sp);
void smoker_remove(smoker_t *sp, char *msg);

#endif /* __SMOKER_H__ */
