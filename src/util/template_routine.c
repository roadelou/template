/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2022-06-25
 * Language: C Source
 * Compiler: cc (GCC) 12.1.1 20220507 (Red Hat 12.1.1-1)
 */

/********************************** INCLUDES **********************************/

// The library we are implementing.
#include <template/util/template_routine.h>

// Used for malloc and free.
#include <stdlib.h>

/* Used for nanosleep. */
#include <time.h>

/********************************* SINGLETONS *********************************/

/* The static global variables for your code goe here. */

/********************************* PROTOYPES **********************************/

/* The prototypes of your functions go here. */

/************************************ MAIN ************************************/

/* The main function of your code goes here. */

/********************************* FUNCTIONS **********************************/

struct TemplateRoutine *new_template_routine(void *(*inner)(void *),
                                             void *argument) {
    //
    // The instance we are going to return.
    struct TemplateRoutine *routine = malloc(sizeof(struct TemplateRoutine));
    ;
    //
    // We set the fields of the routine.
    routine->inner = inner;
    routine->argument = argument;
    routine->result = NULL;
    routine->done = 0;
    //
    // We return the constructed instance.
    return routine;
}

void delete_template_routine(struct TemplateRoutine *routine) {
    //
    // We reset the fields of the routine.
    routine->inner = NULL;
    routine->argument = NULL;
    routine->result = NULL;
    routine->done = 0;
    //
    // We free the memory associated with the routine itself.
    free(routine);
}

void run_template_routine(struct TemplateRoutine *routine) {
    //
    // EDGE CASE
    // =========
    // If the routine has already been executed, we do nothing.
    if (routine->done) {
        //
        // Assembly-style return.
        return;
    }
    //
    // else...
    //
    // We execute the C function, providing the right argument and storing the
    // result.
    routine->result = routine->inner(routine->argument);
    //
    // Finally, we mark the routine as done.
    routine->done = 1;
}

void join_template_routines(size_t count, struct TemplateRoutine **routines) {
    //
    // An iterator to go over each subroutine.
    size_t cursor;
    //
    // A variable used to hold our exit condition.
    int all_joined;
    //
    // The time we will wait before polling the routines to see if they are
    // done. We wait for 10k ns, i.e. 10 us.
    struct timespec idle_wait = {0, 10000};
    //
    // Until all the routines have returned, we wait for them.
    do {
        all_joined = 1;
        //
        // We go over each subroutine.
        for (cursor = 0; cursor < count; cursor++) {
            //
            // We check if the routine has returned and update the loop variable
            // in consequence.
            all_joined &= (*(routines + cursor))->done;
        }
        //
        // We wait a little while before the next iteration.
        nanosleep(&idle_wait, NULL);
    } while (!all_joined);
}

/************************************ EOF *************************************/
