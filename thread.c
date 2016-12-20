/*
// FUNCTIONALITY
// Threads, version 4
// 2016/2017 - 1st Semestre
// Instituto Superior Tecnico
// U.C. Sistemas Operativos
// Rafael Ribeiro, nº 84758
*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include "thread.h"
#include "i-banco.h"
#include "accounts.h"
#include "errorhandling.h"
#include "structure.h"
#include "synchronization.h"
#include "filemanager.h"

//Declares a buffer that stores the waiting-to-be-executed commands.
terminalStruct cmd_buffer[CMD_BUFFER_DIM];
//Declares two semaphores.
sem_t semConsumers;
sem_t semProducers;
//Declares a Mutex.
pthread_mutex_t buffReadMutex;
pthread_mutex_t lock;
//Declares a conditional variable
pthread_cond_t cond;
//Declares a pool of threads.
pthread_t pthreadVector[NUM_TRABALHADORAS];
//Variable that holds the circular buffer's writing index.
//When a new input is detecte, if the given command is on of the ones
//set to run in parallel, the main process writes the correspondent
//structure on the buffer, in the buff_write_idx position;
int buff_write_idx = 0;
//Variable that holds the circular buffer's reading index.
//When a task gets through the semaphre, the information it is going to
//read is stored in the circular buffer's reading index.
int buff_read_idx = 0;
//Variable to store the number of tasks to complete
int count = 0;
//Variable to store the file descriptor of the log file
int fd = 0;

void threadInitialize(){
	int i, retval;
	//Initializes the Mutexes used for critical zones.
	mutexInit(&buffReadMutex);
	mutexInit(&lock);
	condInit(&cond);
	semaphoreInit(&semConsumers, 0);
	semaphoreInit(&semProducers, CMD_BUFFER_DIM);
	//Initializes the threads.
	for (i = 0; i < NUM_TRABALHADORAS; i++)
		if ((retval = pthread_create(&(pthreadVector[i]), NULL, threadConsume, NULL))){
			pthreadCreateErrorHandler(retval);
			exit(EXIT_FAILURE);
		}

	char *filename = "log.txt";
	if ((fd = open(filename, O_CREAT|O_WRONLY|O_TRUNC|O_APPEND, S_IRWXU|S_IRWXG|S_IRWXO)) == 1){ openErrorHandler(); exit(EXIT_FAILURE); }
}

void threadProduce(terminalStruct structure){
	semaphoreWait(&semProducers);
	cmd_buffer[buff_write_idx] = structure;
	buff_write_idx = (buff_write_idx + 1) % CMD_BUFFER_DIM;
	mutexLock(&lock);
	count++;
	mutexUnlock(&lock);
	semaphorePost(&semConsumers);
}

void *threadConsume(void *param){
	while(1){
		int command, fileDescriptorPipe, origin;
		unsigned int len;
		terminalStruct termStruct;
		commandStruct commStruct;

		semaphoreWait(&semConsumers);
		mutexLock(&buffReadMutex);
		termStruct = cmd_buffer[buff_read_idx];
		buff_read_idx = (buff_read_idx + 1) % CMD_BUFFER_DIM;
		mutexUnlock(&buffReadMutex);	
		semaphorePost(&semProducers);
		
		commStruct = termStruct.commStruct;
		command = commStruct.command;
		
		if (command == -1) break;

		len = sizeof(pid_t) + 16;
		char pipename[len];
		snprintf(pipename, len, "i-banco-pipe-%u", termStruct.PID);
		
		origin = fileDup(1);
		fileDescriptorPipe = fileOpen(pipename, O_WRONLY);
		fileDup2(fileDescriptorPipe, fileno(stdout));
		
		if (command == 0) commandCharge(commStruct.accountID1, commStruct.value);
		else if (command == 1) commandCredit(commStruct.accountID1, commStruct.value);
		else if (command == 2) commandReadBalance(commStruct.accountID1);
		else if (command == 3) commandTransfer(commStruct.accountID1, commStruct.accountID2, commStruct.value);
		else printf("ERROR. Unknown command.\n");

		fflush(stdout);
		kill(termStruct.PID, SIGUSR1);
		fileClose(fileDescriptorPipe);
		fileDup2(origin, fileno(stdout));
		threadWriteToLog(commStruct);

		mutexLock(&lock);
		count--;
		condSignal(&cond);
		mutexUnlock(&lock);
	}
	pthread_exit(NULL);
}

void threadComunicate(int numYears){
	mutexLock(&lock);
	while (count != 0) condWait(&cond, &lock);
	commandSimulate(numYears);
	mutexUnlock(&lock);
}

int threadWriteToLog(commandStruct struc){
	long unsigned int len = sizeof(pthread_t) + sizeof(int) * 3 + 32;
	char logEntry[len];
	snprintf(logEntry, len, "%lu: %s", pthread_self(), commandToString(struc));
	fileWrite(fd, logEntry, strlen(logEntry));
	return 0;
}

void threadEnd(){
	int i, retval;
	//Produces structures to indicate the threads to exit.
	for (i = 0; i < 3; i++){
		commandStruct commStruct = { .command = -1, .accountID1 = -1, .accountID2 = -1, .value = -1};
		terminalStruct termStruct = { .commStruct = commStruct, .PID = -1};
		threadProduce(termStruct);
	}
	//Joins with all the threads.
	for (i = 0; i < NUM_TRABALHADORAS; i++)
		if ((retval = pthread_join(pthreadVector[i], NULL))) pthreadJoinErrorHandler(retval);
	
	//Destroys all mutexes and semaphores created.
	semaphoreDestroy(&semConsumers);
	semaphoreDestroy(&semProducers);
	mutexDestroy(&buffReadMutex);
	mutexDestroy(&lock);
	condDestroy(&cond);
	close(fd);
}