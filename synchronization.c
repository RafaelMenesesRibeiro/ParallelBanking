/*
// FUNCTIONALITY
// Synchronization, version 4
// 2016/2017 - 1st Semestre
// Instituto Superior Tecnico
// U.C. Sistemas Operativos
// Rafael Ribeiro, nº 84758
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include "synchronization.h"
#include "errorhandling.h"

int retval;

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//                     FUNCTIONS RELATED WITH MUTEXES                     
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void mutexInit(pthread_mutex_t *mutex){
	if ((retval = pthread_mutex_init(mutex, NULL))){
		mutexInitErrorHandler(retval);
		exit(EXIT_FAILURE);
	}
}

void mutexLock(pthread_mutex_t *mutex){
	if ((retval = pthread_mutex_lock(mutex))) { mutexLockErrorHandler(retval); exit(EXIT_FAILURE); }
}

void mutexUnlock(pthread_mutex_t *mutex){
	while ((retval = pthread_mutex_unlock(mutex))) mutexUnlockErrorHandler(retval);
}

void mutexDestroy(pthread_mutex_t *mutex){
	if (pthread_mutex_destroy(mutex)) mutexDestroyErrorHandler();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//                   FUNCTIONS RELATED WITH SEMAPHORES
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void semaphoreInit(sem_t *semaphore, int i){
	if (sem_init(semaphore, 0, i)){
		semaphoreInitErrorHandler();
		exit(EXIT_FAILURE);
	}
}

void semaphoreWait(sem_t *semaphore){
	if (sem_wait(semaphore)){ semaphoreWaitErrorHandler(); exit(EXIT_FAILURE); }
}

void semaphorePost(sem_t *semaphore){
	if (sem_post(semaphore)) semaphorePostErrorHandler();
}

void semaphoreDestroy(sem_t *semaphore){
	if (sem_destroy(semaphore)) semaphoreDestroyErrorHandler();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//              FUNCTIONS RELATED WITH CONDITION VARIABLES
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void condInit(pthread_cond_t *cond){
	if ((retval = pthread_cond_init(cond, NULL))){
		condInitErrorHandler(retval);
		exit(EXIT_FAILURE);
	}
}

void condWait(pthread_cond_t *cond, pthread_mutex_t *mutex){
	if ((retval = pthread_cond_wait(cond, mutex))){ 
		condWaitErrorHandler(retval);
		mutexUnlock(mutex);
	}
}

void condSignal(pthread_cond_t *cond){
	if ((retval = pthread_cond_signal(cond))) condSignalErrorHandler();
}

void condDestroy(pthread_cond_t *cond){
	if (pthread_cond_destroy(cond)) condDestroyErrorHandler();
}