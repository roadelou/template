/********************************** METADATA **********************************/

/*
* Contributors: roadelou
* Contacts: 
* Creation Date: 2022-08-07
* Language: C Source
* Compiler: cc (GCC) 12.1.1 20220507 (Red Hat 12.1.1-1)
*/

/********************************** INCLUDES **********************************/

/* The testing macros. */
#include <template/test.h>

/* The library under test. */
#include <template/util/job_queue.h>

/* Used for the SUCCESS and ERROR values. */
#include <template/util/base.h>

/********************************* SINGLETONS *********************************/

/* The static global variables for your code goe here. */

/********************************* PROTOYPES **********************************/

// Test for the new_job_queue function.
void test_new_job_queue(void);

/************************************ MAIN ************************************/

int main(int argc, const char **argv) {
    test_new_job_queue();
}

/********************************* FUNCTIONS **********************************/

void test_new_job_queue(void) {
	struct JobQueue *job_queue = new_job_queue();
	//
	// We check that the internal state of the JobQueue is correct.
	TEST_INTEGER(0, job_queue->head);
	TEST_INTEGER(0, job_queue->pending);
	TEST_INTEGER(0, job_queue->allocated);
	//
	// We try to acquire the lock.
	int status = pthread_mutex_trylock(job_queue->lock);
	TEST_INTEGER(0, status);
	//
	// We free the lock before freeing the memory.
	pthread_mutex_unlock(job_queue->lock);
	//
	// Calling the destructor.
	delete_job_queue(job_queue);
}

/************************************ EOF *************************************/
