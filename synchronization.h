/*
// HEADER
// Synchronization, version 4
// 2016/2017 - 1st Semestre
// Instituto Superior Tecnico
// U.C. Sistemas Operativos
// Rafael Ribeiro, nº 84758
*/

#ifndef SYNCHRONIZATION_H
#define SYNCHRONIZATION_H

#include <semaphore.h>

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//                     FUNCTIONS RELATED WITH MUTEXES                     
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void mutexInit(pthread_mutex_t *mutex);

void mutexLock(pthread_mutex_t *mutex);

void mutexUnlock(pthread_mutex_t *mutex);

void mutexDestroy(pthread_mutex_t *mutex);

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//                   FUNCTIONS RELATED WITH SEMAPHORES
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void semaphoreInit(sem_t *semaphore, int i);

void semaphoreWait(sem_t *semaphore);

void semaphorePost(sem_t *semaphore);

void semaphoreDestroy(sem_t *semaphore);

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//              FUNCTIONS RELATED WITH CONDITION VARIABLES
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void condInit(pthread_cond_t *cond);

void condWait(pthread_cond_t *cond, pthread_mutex_t *mutex);

void condSignal(pthread_cond_t *cond);

void condDestroy(pthread_cond_t *cond);

#endif