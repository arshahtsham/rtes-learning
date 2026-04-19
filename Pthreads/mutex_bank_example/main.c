#include <stdio.h>
#include <pthread.h>
#include "bank.h"


void* deposit(void *amount);

// mutex variable
pthread_mutex_t mutex;

int main()
{
  // output the balance before the deposits
  int before = read_balance();
  printf("Before: %d\n", before);
  
  // we'll create two threads to conduct a deposit using the deposit function
  pthread_t thread1;
  pthread_t thread2;
  
  // initialize the mutex
  pthread_mutex_init(&mutex, NULL);

  // the deposit amounts... the correct total afterwards should be 500
  int deposit1 = 300;
  int deposit2 = 200;
  
  // create threads to run the deposit function with these deposit amounts
  pthread_create(&thread1, NULL, deposit, (void*) &deposit1);
  pthread_create(&thread2, NULL, deposit, (void*) &deposit2);
  
  // join the threads
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  
  // destroy the mutex
  pthread_mutex_destroy(&mutex);

  // output the balance after the deposits
  int after = read_balance();
  printf("After: %d\n", after);

  return 0;
}


void* deposit(void *amount)
{

  pthread_mutex_lock(&mutex);

  int account_balance = read_balance();
  
  account_balance += *((int *) amount); 
  
  write_balance(account_balance);
  
  pthread_mutex_unlock(&mutex);

  return NULL;
}

