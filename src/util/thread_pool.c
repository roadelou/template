/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2022-05-25
 * Language: C Source
 * Compiler: cc (GCC) 12.1.1 20220507 (Red Hat 12.1.1-1)
 */

/********************************** INCLUDES **********************************/

// The library we are implementing.
#include <template/util/thread_pool.h>

// Used for nanosleep.
#include <time.h>

// Used for malloc and free.
#include <stdlib.h>

/********************************* SINGLETONS *********************************/

/* The static global variables for your code goe here. */

/********************************* PROTOYPES **********************************/

// Description
// ===========
// The main function of the threads in the ThreaPool.
//
static void *thread_main(void *thread_pool_ptr);

/************************************ MAIN ************************************/

/* The main function of your code goes here. */

/********************************* FUNCTIONS **********************************/

struct ThreadPool *new_thread_pool(size_t threads_count) {
    //
    // An iterator for our for loop.
    size_t cursor;
    //
    // We allocate the memory for the threadPool itself.
    struct ThreadPool *pool = malloc(sizeof(struct ThreadPool));
    //
    // We set the size of the pool.
    pool->size = threads_count;
    //
    // The threads shouldn't shutdown yet.
    pool->shutdown = 0;
    //
    // We allocate the memory for the threads themselves.
    pool->threads = malloc(threads_count * sizeof(pthread_t));
    //
    // We build the JobQueue before the threads are started.
    pool->queue = new_job_queue();
    //
    // We start every thread individually.
    for (cursor = 0; cursor < threads_count; cursor++) {
        //
        // We create the thread, which runs our static thread_main function. We
        // give our threads a reference to the ThreadPool itself so that they
        // have access to the shutdown value and to the JobQueue.
        pthread_create(pool->threads + cursor, NULL, &thread_main,
                       (void *)pool);
    }
    //
    // The initialization is done, we return our ThreadPool.
    return pool;
}

void delete_thread_pool(struct ThreadPool *pool) {
    //
    // A cursor used for our loops.
    size_t cursor;
    //
    // We start by killing every thread.
    pool->shutdown = 1;
    //
    // Now that the signal has been sent, we wait for our threads to finish.
    for (cursor = 0; cursor < pool->size; cursor++) {
        pthread_join(*(pool->threads + cursor), NULL);
    }
    //
    // Now that the threads are dead, we can safely destroy the other elements.
    pool->size = 0;
    delete_job_queue(pool->queue);
    //
    // We free the memory for the threads.
    free(pool->threads);
    //
    // Finally, we free the memory associated with the ThreadPool itself.
    free(pool);
}

static void *thread_main(void *thread_pool_ptr) {
    //
    // Whe first cast the ThreadPool to its real type.
    struct ThreadPool *pool = thread_pool_ptr;
    //
    // The current routine we are running.
    template_routine routine;
    //
    // The argument for the current routine.
    void *argument;
    //
    // The time we will wait before polling the JobQueue again if it was empty.
    // We wait for 10k ns, i.e. 10 us.
    struct timespec idle_wait = {0, 10000};
    //
    // We enter the main loop.
    while (!pool->shutdown) {
        //
        // We acquire the lock to the queue.
        pthread_mutex_lock(pool->queue->lock);
        //
        // Now that we have the lock, we check whether there are pending jobs.
        if (pool->queue->pending > 0) {
            //
            // We grab the routine and its argument.
            pop_job_queue(pool->queue, &routine, &argument);
            //
            // We release the queue before starting the computation for the
            // next threads.
            pthread_mutex_unlock(pool->queue->lock);
            //
            // We call the provided routine.
            (*routine)(argument);
            //
            // We assume that the ThreadPool is quite busy, hence we don't wait
            // here and try polling the JobQueue immediately.
        } else {
            //
            // If there are no pending jobs, we release the lock for the next
            // thread.
            pthread_mutex_unlock(pool->queue->lock);
            //
            // We assume that there ThreadPool is idle, hence we wait for a few
            // microseconds before polling the JobQueue again.
            nanosleep(&idle_wait, NULL);
        }
    }
    //
    // Once the treads shuts down we return NULL.
    return NULL;
}

/************************************ EOF *************************************/
