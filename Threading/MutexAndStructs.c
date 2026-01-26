#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int balance = 1000;
pthread_mutex_t lock;

// 1. Define a struct for the transaction amount
typedef struct Transaction {
    int deposit;
    int withdraw;
} Transaction;

// 2. Write the transaction function
//    - Cast the argument.
//    - Loop 5 times.
//    - Lock, Modify Balance, Print "Deposited/Withdrew X, Balance: Y", Unlock.
//    - Sleep(1) to make the interleaving obvious.
void* handleTransaction(void* ptr){
    Transaction* t = (Transaction*) ptr;

    for(int i = 0; i <5; i++){
        pthread_mutex_lock(&lock);
        balance += t->deposit;
        balance -= t->withdraw;
        pthread_mutex_unlock(&lock);
    }
    free(t);
}

int main() {
    pthread_mutex_init(&lock, NULL);
    pthread_t t1, t2;

    // 3. Create arguments (malloc structs)
    //    - Arg1: amount = 100
    //    - Arg2: amount = -50
    Transaction* deposit = (Transaction*)malloc(sizeof(Transaction));
    deposit->deposit = 100;
    deposit->withdraw = 0;
    Transaction* withdraw = (Transaction*)malloc(sizeof(Transaction));
    withdraw->withdraw = 50;
    deposit->deposit = 0;
    
    // 4. Create threads
    if(pthread_create(&t1,NULL, handleTransaction, deposit) != 0){
        perror("Deposit thread creatin failed");
    }

    if(pthread_create(&t2,NULL, handleTransaction, withdraw) != 0){
        perror("Withdraw thread creatin failed");
    }
    
    // 5. Join threads
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    // void* retval;
    // pthread_exit(retval);
    pthread_mutex_destroy(&lock);
    
    // 6. Print final balance & Cleanup
    printf("%d", balance);
    
    return 0;
}