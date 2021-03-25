/*
  Name: Karanveer Sandhu
  PID: 6096890
  I hearby declare that this source code is original
  and not anyone else's work except for Professor Caryl Rahn.
*/

/*
  Program Description:
  This program uses 10 threads to increment a global variable.
  Each thread increments the global variable by the thread ID and
  each thread does this 6 times as a loop.
  The global variable is then printed to the screen.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10

/* create thread argument struct for thr_func() */
typedef struct _thread_data_t {
  int tid; // the thread's id.
} thread_data_t;

/* shared data between threads */
int shared_x;
pthread_mutex_t lock_x;

// This function increments the shared_x by the thread's ID number
// 6 times each.
void *thr_func(void *arg) {

  // since the parameter is a void pointer. We need to upcast the parameter
  // into a thread_data_t object.
  thread_data_t *data = (thread_data_t *)arg;

  // pass "talking stick" to the thread.
  pthread_mutex_lock(&lock_x);
  
  // loop 6 times.
  int j;
  for (j = 0; j < 6; j++)
  {
    shared_x += data->tid; // increment shared_x by the thread's id.
  }
  
  // After looping, print the ID of the thread
  printf("Thread [%d] has finished.\n", data->tid);

  // relinquish the "talking stick" from the thread.
  pthread_mutex_unlock(&lock_x);
  
  // exit the thread.
  pthread_exit(NULL);
}

int main(int argc, char **argv) {

  // integer used to identify the thread in the system
  pthread_t thr[NUM_THREADS];
  
  // i is used to loop to make the threads
  // rc is used to see if making the thread creates an error.
  int i, rc;

  /* create a thread_data_t argument array */
  thread_data_t thr_data[NUM_THREADS];

  /* initialize shared data */
  shared_x = 0;

  /* initialize pthread mutex protecting "shared_x" */
  pthread_mutex_init(&lock_x, NULL);

  /* create threads and do the function.*/
  for (i = 0; i < NUM_THREADS; ++i) {
    thr_data[i].tid = i;
    if ((rc = pthread_create(&thr[i], NULL, thr_func, &thr_data[i]))) {
      fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
      return EXIT_FAILURE;
    }
  }

  /* block until all threads complete */
  for (i = 0; i < NUM_THREADS; ++i) {
    pthread_join(thr[i], NULL);
  }

  printf("Final value: %d\n", shared_x);

  return EXIT_SUCCESS;
}
