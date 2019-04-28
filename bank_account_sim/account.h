#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define INT_BALANCE 40000
#define ROUND 40000

typedef struct {
  char name[31];
  int id;
  int balance;
  sem_t mutex;
  sem_t money;
} account_info;

void account_init(account_info *sp, int n);
void account_deposit(account_info *sp, int tid, int amount);
void account_withdraw(account_info *sp, int tid, int amount);
