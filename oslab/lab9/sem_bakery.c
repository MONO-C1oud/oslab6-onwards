#include "pthread.h" /*Importing the thread library */
#include "stdio.h"
#include "unistd.h" /*Importing POSIX Operating System API library*/
#include "string.h"
#include "semaphore.h"
#include <stdlib.h>
#include <semaphore.h> // The maximum number of customer threads.
#include <time.h>

#define MEMBAR __sync_synchronize() /* memory barrier instruction*/
int res;


sem_t binsem;

// CRITICAL Section
void use_res(int thread)
{
    sem_wait(&binsem); //locks the critical section
    if (res != 0)
    {
        printf("The Resource was acquired by %d, but is still in-use by %d!\n",      thread, res);
    }
    res = thread;
    printf("%d is using resource...\n", thread);

    MEMBAR;
    //sleep(2); //commented to make the program run quicker for execution time analysis
    res = 0;
    sem_post(&binsem); //unlocks the critical section
}

//Simplified function to show the implementation
void *thread_body(void *arg)
{
    long thread = (long)arg;
    use_res(thread);
    return NULL;
}

int main(int argc, char **argv)
{
    clock_t start, end;
    start = clock();
    sem_init(&binsem, 0, 1); //initializing the semaphore
    res = 0;

    // Declaring the thread variables
    int THREAD_COUNT = atoi(argv[1]);
    pthread_t threads[THREAD_COUNT];


    for (int i = 0; i < THREAD_COUNT; ++i)
    {
        // Creating a new thread with the function
        //"thread_body" as its thread routine
        pthread_create(&threads[i], NULL, &thread_body, (void *)((long)i));
    }
    for (int i = 0; i < THREAD_COUNT; ++i)
    {
        // Reaping the resources used by
        // all threads once their task is completed.
        pthread_join(threads[i], NULL);
    }
    end = clock();
    double exectime = ((double)end - start)/CLOCKS_PER_SEC;
    printf("\nProgram finished execution in %f\n", exectime);
    return 0;
}