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

// Used for the TemplateRoutine definition.
#include <template/util/template_routine.h>

// Used for nanosleep.
#include <time.h>

// Used for malloc and free.
#include <stdlib.h>

/********************************* SINGLETONS *********************************/

// The global thread pool instance provided for convenience.
struct ThreadPool *GLOBAL_THREAD_POOL;

/********************************* PROTOYPES **********************************/

/// Description
/// ===========
/// The main function of the threads in the ThreaPool. It instructs the thread to
/// run any job submitted to the pool.
///
/// Arguments
/// =========
///  - thread_pool_ptr: Apointer to the threadpool itself, which contains the
///  queue of jobs which should be run.
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
    // We check for a malloc fail here since threads_count is provided by the
    // user.
    if (pool->threads == NULL) {
        free(pool);
        return NULL;
    }
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
    struct TemplateRoutine *routine;
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
            pop_job_queue(pool->queue, &routine);
            //
            // We release the queue before starting the computation for the
            // next threads.
            pthread_mutex_unlock(pool->queue->lock);
            //
            // We call the provided routine.
            run_template_routine(routine);
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
