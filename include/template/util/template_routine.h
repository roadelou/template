/* Include once header guard */
#ifndef TEMPLATE_ROUTINE_INCLUDED
#define TEMPLATE_ROUTINE_INCLUDED

/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2022-06-25
 * Language: C Header
 * Compiler: cc (GCC) 12.1.1 20220507 (Red Hat 12.1.1-1)
 */

/********************************** INCLUDES **********************************/

/* Used for the NULL definition. */
#include <stddef.h>

/*********************************** MACROS ***********************************/

/* The macros definitions for your header go here */

/********************************** STRUCTS ***********************************/

/* The enums of your header go here */

/** Description
 * ===========
 * A subroutine which can be run asynchronously by the thread pool.
 * */
struct TemplateRoutine {
    void *(*inner)(void *); ///< A pointer to the C function which should be run in this routine.
    void *argument; ///< The argument which should be provided to the function when it runs.
    void *result; ///< A pointer which will be populated with the result of the function once it has been run.
    int done; ///< A boolean telling whether the execution of the routine is over.
};

/* The unions of your header go here */

/** This typedef provides a more readable way to cast functions for routines. */
typedef void *raw_routine(void *);

/********************************* PROTOTYPES *********************************/

/** Description
 * ===========
 * Constructor of the TemplateRoutine struct.
 *
 * Arguments
 * =========
 *  - inner: The C function which should be run inside of the routine.
 *  - argument: A pointer to the argument which should be provided to the
 *  function.
 *
 * Returns
 * =======
 * The constructed TemplateRoutine instance.
 * */
struct TemplateRoutine *new_template_routine(void *(*inner)(void *),
                                             void *argument);

/** Description
 * ===========
 * Destructor of the TemplateRoutine struct.
 *
 * Arguments
 * =========
 *  - routine: The instance which should be collected.
 *
 * Side-effects
 * ============
 * The instance will be collected.
 * */
void delete_template_routine(struct TemplateRoutine *routine);

/** Description
 * ===========
 * Runs the provided routine, if it hasn't been marked as done already.
 *
 * Arguments
 * =========
 *  - routine: The routine which should be run.
 *
 * Side-effects
 * ============
 * Any side-effects from the C function inside of the routine will take place.
 * The result field of the routine will be updated, and the it will be marked as
 * done.
 * */
void run_template_routine(struct TemplateRoutine *routine);

/** Description
 * ===========
 * Blocks until every provided routine has been executed.
 *
 * Arguments
 * =========
 *  - count: The number of routines we should wait for.
 *  - routines: An array of routines which should be waited for.
 *
 * Side-effects
 * ============
 * The execution flow will block until all the routines have returned, which
 * could lead to deadlocks.
 * */
void join_template_routines(size_t count, struct TemplateRoutine **routines);

/* End of include once header guard */
#endif

/************************************ EOF *************************************/
