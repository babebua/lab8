#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "account.h"
#include "common_threads.h"

account_info *account_database;
pthread_t *borrower_list;
pthread_t *lender_list;

void *lender(void *arg) // Finish
{
    int tid = (int)arg;
    int i;

    printf("I am lender # %d\n", tid);

    for (i = 0; i < ROUND; i++)
        account_deposit(account_database, tid, 2);

    return NULL;
}

void *borrower(void *arg) // Finish
{
    int tid = (int)arg;
    int i;

    printf("I am borrower # %d\n", tid);

    for (i = 0; i < ROUND; i++)
        account_withdraw(account_database, tid, 1);

    return NULL;
}

int main(int argc, char *argv[]) {
    int i, num_account;

    num_account = 4;
    printf("size of account_info is %d; size of int is %d; size of void "
           "pointer is %d\n",
           sizeof(account_info), sizeof(int), sizeof(void *));
    account_database =
        (account_info *)malloc(sizeof(account_info) * num_account);
    if (account_database == NULL) {
        fprintf(stderr, "Malloc unsuccessful\n");
        exit(0);
    }

    // Initialize account_database
    account_init(account_database, num_account);
    for (i = 0; i < num_account; i++) {
        printf("Account: %d; name: %s; balance: %d\n", i,
               account_database[i].name, account_database[i].balance);
    }
    printf("\n");

    borrower_list = (pthread_t *)malloc(sizeof(pthread_t) * num_account);
    lender_list = (pthread_t *)malloc(sizeof(pthread_t) * num_account);

    for (i = 0; i < num_account; i++) {
        int tid = i;
        Pthread_create(&lender_list[i], NULL, lender, (void *)tid);
        Pthread_create(&borrower_list[i], NULL, borrower, (void *)tid);
    }

    for (i = 0; i < num_account; i++) {
        Pthread_join(lender_list[i], NULL);
        Pthread_join(borrower_list[i], NULL);
    }

    printf("\n");

    for (i = 0; i < num_account; i++) {
        printf("Account: %d; name: %s; balance: %d\n", i,
               account_database[i].name, account_database[i].balance);
    }
    return 0;
}
