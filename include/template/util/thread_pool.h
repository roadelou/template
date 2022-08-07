/* Include once header guard */
#ifndef TEMPLATE_UTIL_THREADS_POOL_INCLUDED
#define TEMPLATE_UTIL_THREADS_POOL_INCLUDED

/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2022-05-25
 * Language: C Header
 * Compiler: cc (GCC) 12.1.1 20220507 (Red Hat 12.1.1-1)
 */

/********************************** INCLUDES **********************************/

// Used for the pthreads types.
#include <pthread.h>

// Used for the JobQueue type.
#include <template/util/job_queue.h>

/*********************************** MACROS ***********************************/

/* The macros definitions for your header go here */

/********************************** STRUCTS ***********************************/

/* The enums of your header go here */

/// Description
/// ===========
/// This struct is used to create a threadpool and run several tasks in
/// parallel.
///
struct ThreadPool {
    size_t size;            ///< The amount of threads in the pool.
    int shutdown;           ///< Whether the ThreadPool is shutting down.
    pthread_t *threads;     ///< The list of threads available.
    struct JobQueue *queue; ///< The queue used to submit new jobs.
};

/* The unions of your header go here */

/* The typedefs of your header go here */

/// Description
/// ===========
/// This is the global threadpool made available during the execution. It should
/// be initialized before its use.
extern struct ThreadPool *GLOBAL_THREAD_POOL;

/********************************* PROTOTYPES *********************************/

/// Description
/// ===========
/// Constructor of the ThreadPool class.
///
/// Arguments
/// =========
///  - thread_count: the number of threads we want to use in our ThreadPool.
///
/// Returns
/// =======
/// This constructor will return an instance of ThreadPool ready to be used.
///
/// Side-effects
/// ============
/// The threads in the pool will be started, waiting for jobs to be submitted in
/// the JobQueue.
///
struct ThreadPool *new_thread_pool(size_t threads_count);

/// Description
/// ===========
/// Destructor of the ThreadPool class.
///
/// Arguments
/// =========
///  - pool: the TreadPool instance which should be collected.
///
/// Returns
/// =======
/// This call returns nothing.
///
/// Side-effects
/// ============
/// The threads will be joined and the memory associated with the ThreadPool
/// will be freed.
///
void delete_thread_pool(struct ThreadPool *pool);

/* End of include once header guard */
#endif

/************************************ EOF *************************************/
