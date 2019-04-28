/* $begin sbufc */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#include "common_threads.h"
#include "sbuf.h"

/* Create an empty, bounded, shared FIFO buffer with n slots */
/* $begin sbuf_init */
void sbuf_init(sbuf_t *sp, int n)
{
  void *p;
  assert((p = calloc(n, sizeof(int))) != NULL);
  sp->buf = p;
  assert((p = calloc(n, sizeof(char))) != NULL);
  sp->id = p;
  sp->n = n;                       /* Buffer holds max of n items */
  sp->front = sp->rear = 0;        /* Empty buffer iff front == rear */
  Sem_init(&sp->mutex, 0, 1);      /* Binary semaphore for locking */
  Sem_init(&sp->slots, 0, n);      /* Initially, buf has n empty slots */
  Sem_init(&sp->items, 0, 0);      /* Initially, buf has zero data items */
}
/* $end sbuf_init */

/* Clean up buffer sp */
/* $begin sbuf_deinit */
void sbuf_deinit(sbuf_t *sp)
{
  free(sp->buf);
}
/* $end sbuf_deinit */

/* Insert item onto the rear of shared buffer sp */
/* $begin sbuf_insert */
void sbuf_insert(sbuf_t *sp, int item, char *msg)
{
  int index;
  P(&sp->slots);                          /* Wait for available slot */
  P(&sp->mutex);                          /* Lock the buffer */
  index = (++sp->rear)%(sp->n);
  sp->buf[index] = item;   /* Insert the item */
  sp->id[index] = msg[0];
  printf("I am a PRODUCER # %c inserting item %d from PRODUCER # %c\n", sp->id[index], item, sp->id[index]);
  printf("Number of items in queue now is %d\n", sp->rear - sp->front);
  sleep(1);
  V(&sp->mutex);                          /* Unlock the buffer */
  V(&sp->items);                          /* Announce available item */
}
/* $end sbuf_insert */

/* Remove and return the first item from buffer sp */
/* $begin sbuf_remove */
int sbuf_remove(sbuf_t *sp, char *msg)
{
  int item, index;
  P(&sp->items);                          /* Wait for available item */
  P(&sp->mutex);                          /* Lock the buffer */
  index = (++sp->front)%(sp->n);
  item = sp->buf[index];  /* Remove the item */
  printf("I am a consumer # %c consuming item %d from producer # %c\n", msg[0], item, sp->id[index]);
  printf("Number of items in queue now is %d\n", sp->rear - sp->front);
  sleep(1);
  V(&sp->mutex);                          /* Unlock the buffer */
  V(&sp->slots);                          /* Announce available slot */
  return item;
}
/* $end sbuf_remove */
/* $end sbufc */
