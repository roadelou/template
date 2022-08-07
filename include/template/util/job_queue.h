/* Include once header guard */
#ifndef TEMPLATE_UTIL_JOB_QUEUE_INCLUDED
#define TEMPLATE_UTIL_JOB_QUEUE_INCLUDED

/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2022-05-25
 * Language: C Header
 * Compiler: cc (GCC) 12.1.1 20220507 (Red Hat 12.1.1-1)
 */

/********************************** INCLUDES **********************************/

/** Used for the TemplateRoutine definition, */
#include <template/util/template_routine.h>

/** Used for the threading types. */
#include <pthread.h>

/*********************************** MACROS ***********************************/

/// The allocation size for the JobQueue routines and arguments arrays.
#ifndef TEMPLATE_JOB_SERVER_CHUNK_SIZE
#define TEMPLATE_JOB_SERVER_CHUNK_SIZE 4
#endif

/********************************** STRUCTS ***********************************/

/* The enums of your header go here */

/// Description
/// ===========
/// This structure is used to describe a queue of jobs which should be executed
/// by a ThreadPool.
struct JobQueue {
    pthread_mutex_t *lock; ///< A lock to ensure that multiple threads aren't
                           ///< writing to the queue of jobs at once.
    size_t head;           ///< The index of the next job to run in the queue.
    size_t pending;        ///< The number of pending jobs in the ThreadPool.
    size_t allocated; ///< The number of elements allocated for the routines and
                      ///< the arguments.
    struct TemplateRoutine *
        *routines; ///< The functions which should be called for the next jobs.
};

/* The unions of your header go here */

/********************************* PROTOTYPES *********************************/

/// Description
/// ===========
/// Constructor for the JobQueue class.
///
/// Arguments
/// =========
/// This method takes no arguments.
///
/// Returns
/// =======
/// The constructor returns a new heap-allocated JobQueue, which has to be freed
/// by the caller once it isn't needed anymore.
///
/// Side-effects
/// ============
/// This method has no side-effects.
///
struct JobQueue *new_job_queue(void);

/// Description
/// ===========
/// Destructor for the JobQueue class.
///
/// Arguments
/// =========
///  - queue: A pointer to the JobQueue which should be collected.
///
/// Returns
/// =======
/// This functions returns nothing.
///
/// Side-effects
/// ============
/// The provided JobQueue will be collected and the memory associated will be
/// freed.
///
void delete_job_queue(struct JobQueue *queue);

/// Description
/// ===========
/// Submits a new job to the JobQueue.
///
/// Arguments
/// =========
///  - queue: A pointer to the queue in which the job should be submitted.
///  - routine: The code which should be run during the job.
///  - argument: The argument provided to the routine once it will be launched.
///
/// Returns
/// =======
/// This function returns nothing.
///
/// Side-effects
/// ============
/// This functions will hang until it can acquire the lock to the JobQueue.
/// Also, if the JobQueue has drifted in memory because of too many push/pop, a
/// clean-up may be initiated.
///
void push_job_queue(struct JobQueue *queue, struct TemplateRoutine *routine);

/// Description
/// ===========
/// Removes the oldest job from the JobQueue. The lock to the queue MUST have
/// been acquired BEFORE calling this function.
///
/// Arguments
/// =========
///  - routine: A pointer to a pointer of a routine, a side-effect will set it
///  to the routine of the old job.
///
/// Returns
/// =======
/// This function returns nothing.
///
/// Side-effects
/// ============
/// The old job is removed from the JobQueue and routine and argument are set to
/// the expected values.
///
void pop_job_queue(struct JobQueue *queue, struct TemplateRoutine **routine);

/* End of include once header guard */
#endif

/************************************ EOF *************************************/
