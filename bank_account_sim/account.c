#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "common_threads.h"
#include "account.h"

void account_init(account_info *sp, int n)
{
    int i;
    for (i=0; i<n; i++) {
        sprintf(sp[i].name, "%s%d", "test_account", i);
        sp[i].id = i;
        sp[i].balance = INT_BALANCE;
	Sem_init(&sp[i].mutex,0,1);
    }
}

void account_deposit(account_info *sp, int tid, int amount)
{
   P(&sp[tid].mutex);
   sp[tid].balance += amount;
   V(&sp[tid].mutex);
   V(&sp[tid].money);
}

void account_withdraw(account_info *sp, int tid, int amount)
{
   P(&sp[tid].mutex);
    while (sp[tid].balance < amount) {
        printf("Not enough funds to withdraw!\n");
	V(&sp[tid].mutex);
	P(&sp[tid].money);
	P(&sp[tid].mutex);
	return ;
    }

    sp[tid].balance -= amount;
   V(&sp[tid].mutex)
}


