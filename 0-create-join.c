/* 
 * Illustrate basic use of pthreads:  
 * create some threads, each of which prints a message.
 * 
 * gcc <name.c> -o <name> -lpthread
 
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
    void *(*start_routine) (void *), void *arg);
 */
/*---
MinGW, Minimalist GNU for Windows, is a minimalist development 
environment for native Microsoft Windows applications.

mingw-w64: GCC for Windows 64 & 32 bits
https://www.mingw-w64.org/
https://sourceforge.net/projects/mingw-w64/
---*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 

// global variable: accessible to all threads
int thread_count;  

// thread function
void *hello(void* rank) {
    long my_rank = (long) rank;  

    printf("--Hello--"); 
    printf("from thread %ld of %d\n", my_rank, thread_count);

    return NULL;
}

//--------------------------------
int main(int argc, char* argv[]) {
    long       t;  
    pthread_t* thread_handles; 

    thread_count = 4;
    
    // get number of threads from command line
    if (argc > 1) 
        thread_count = atoi(argv[1]);  
   
    thread_handles = malloc(thread_count * sizeof(pthread_t)); 

    // Create independent threads
    for (t = 0; t < thread_count; t++)  
        pthread_create(&thread_handles[t], NULL,
                hello, (void*) t);  

    printf("Hello from the main thread\n");

    // wait till threads are complete before main continues
    for (t = 0; t < thread_count; t++) 
        pthread_join(thread_handles[t], NULL); 

    printf("done\n");

    free(thread_handles);
    return 0;
}
