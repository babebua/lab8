#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#include "common_threads.h"
#include "sbuf.h"

sbuf_t *shared_data;

void *producer(void *arg)
{
  char *msg = arg;
  int item = 1;
  while (1) {
    sbuf_insert(shared_data, item, msg);
    item++;
    if (item == 6) item = 1;
  }
  
  return NULL;
}  

void *consumer(void *arg)
{
  char *msg = arg;
  int item;
  while (1) {
    item = sbuf_remove(shared_data, msg);
  }
  
  return NULL;
}

int main(int argc, char *argv[])
{

  pthread_t p1, p2, p3, p4;

  printf("size of sd = %lu\n", sizeof(sbuf_t));
  shared_data = malloc(sizeof(sbuf_t));
  if (shared_data == NULL) {
    fprintf(stderr, "Malloc unsuccessful\n");
    exit(0);
  }
  // Initialize buffer of size 5
  sbuf_init(shared_data, 5);
  
  Pthread_create(&p1, NULL, consumer, "1");
  Pthread_create(&p2, NULL, producer, "1");
  Pthread_create(&p3, NULL, consumer, "2");
  Pthread_create(&p4, NULL, producer, "2");

  // join waits for the threads to finish
  Pthread_join(p1, NULL);
  Pthread_join(p2, NULL);
  Pthread_join(p3, NULL);
  Pthread_join(p4, NULL);

  return 0;
}
