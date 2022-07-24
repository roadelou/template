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
#include <template/util/job_queue.h>

// Used for memmove.
#include <string.h>

// Used for malloc and free.
#include <stdlib.h>

/********************************* SINGLETONS *********************************/

/* The static global variables for your code goe here. */

/********************************* PROTOYPES **********************************/

// Description
// ===========
// Helper function, returns 1 if an automatic clean-up of the JobQueue should
// take place.
//
static int should_clean_queue(struct JobQueue *queue);

// Description
// ===========
// Helper function whic performs an automatic cleanup of the provided queue.
//
static void clean_queue(struct JobQueue *queue);

/************************************ MAIN ************************************/

/* The main function of your code goes here. */

/********************************* FUNCTIONS **********************************/

struct JobQueue *new_job_queue(void) {
    // We allocate the memory for the JobQueue.
    struct JobQueue *queue = malloc(sizeof(struct JobQueue));
    //
    // We allocate some memory for the lock of the queue.
    queue->lock = malloc(sizeof(pthread_mutex_t));
    //
    // We initialize the mutex of the queue.
    pthread_mutex_init(queue->lock, NULL);
    //
    // The queue is initially empty.
    queue->head = 0;
    queue->pending = 0;
    queue->allocated = 0;
    queue->routines = NULL;
    //
    // We return the initialized JobQueue.
    return queue;
}

void delete_job_queue(struct JobQueue *queue) {
    //
    // We first have to aquire the lock, as described in the man page of
    // pthread_mutex_destroy.
    pthread_mutex_lock(queue->lock);
    //
    // While we have the lock, we collect the other fields of the JobQueue.
    queue->head = 0;
    queue->pending = 0;
    queue->allocated = 0;
    //
    // We free any memory associated with the pending routines and arguments.
    free(queue->routines);
    //
    // One we have the mutex available, we release it and destroy it.
    pthread_mutex_unlock(queue->lock);
    pthread_mutex_destroy(queue->lock);
    //
    // We free the memory associated with the lock itself.
    free(queue->lock);
    //
    // Finally, we release the memory associated with the JobQueue itself.
    free(queue);
}

void push_job_queue(struct JobQueue *queue, struct TemplateRoutine *routine) {
    //
    // We first acquire the lock to the queue.
    pthread_mutex_lock(queue->lock);
    //
    // If it makes sense, we cleanup the queue.
    if (should_clean_queue(queue)) {
        clean_queue(queue);
    }
    //
    // EDGE CASE
    // =========
    // If we have reached the end of an allocated block, we allocate more space
    // for the next routine and argument.
    if (queue->allocated % TEMPLATE_JOB_SERVER_CHUNK_SIZE == 0) {
        //
        // We raise the number of allocated elements.
        queue->allocated += TEMPLATE_JOB_SERVER_CHUNK_SIZE;
        //
        // We assume that realloc doesn't fail here since this requires very
        // little memory.
        queue->routines = realloc(
            queue->routines, queue->allocated * sizeof(struct TemplateRoutine));
    }
    //
    // else...
    //
    // We add the new routine and argument in the queue.
    *(queue->routines + queue->head + queue->pending) = routine;
    //
    // We raise the number of pending jobs.
    queue->pending++;
    //
    // We are done here, we release the lock.
    pthread_mutex_unlock(queue->lock);
}

void pop_job_queue(struct JobQueue *queue, struct TemplateRoutine **routine) {
    //
    // In a threadpool context, it only makes sense to call this function after
    // the lock has been acquired, hence we cannot re-aquire it here, otherwise
    // the program reaches a deadlock.
    // pthread_mutex_lock(queue->lock);
    //
    // We set the routine and the argument tot he value specified in the
    // JobQueue.
    *routine = *(queue->routines + queue->head);
    //
    // There is one less pending job in the queue, and the head moves to the
    // next pending job.
    queue->pending--;
    queue->head++;
    //
    // We don't free the lock since we didn't need to acquire it in the first
    // place.
    // pthread_mutex_unlock(queue->lock);
}

static int should_clean_queue(struct JobQueue *queue) {
    //
    // If there is at least 3 empty chunks at the beginning of the JobQueue,
    // we start a cleanup.
    return queue->head > 3 * TEMPLATE_JOB_SERVER_CHUNK_SIZE;
}

static void clean_queue(struct JobQueue *queue) {
    //
    // We assume that we already have the lock to the queue at this point. We
    // are simply going to move the head of the queues back to 0.
    memmove(queue->routines, queue->routines + queue->head,
            queue->pending * sizeof(struct TemplateRoutine));
    //
    // We reset the head of the JobQueue back to 0 to point to the oldest job.
    queue->head = 0;
}

/************************************ EOF *************************************/
