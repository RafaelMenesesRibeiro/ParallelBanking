/*
// FUNCTIONALITY
// Error handling, version 3
// 2016/2017 - 1st Semestre
// Instituto Superior Tecnico
// U.C. Sistemas Operativos
// Rafael Ribeiro, nº 84758
*/

#include <stdio.h>
#include <errno.h>
#include <ctype.h>

void syntaxErrorMsg(char command[]){ printf("%s: Syntax error.\n", command); }

void valueErrorMsg(char command[], int accountID, int value){ printf("%s(%d, %d): Argument error.\n", command, accountID, value); }

int checkIsValid(int argNum, char **args){
	int i = 1;
	for (i = 1; i <= argNum; i++){
		char *arg = args[i];
		if (arg == NULL){
			printf("%s: Argument error.\n", args[0]);
			return -1;
		}
		//Checks if all the characters are digits (through isdigit function).
		int j = 0;
		for (j = 0; arg[j] != '\0'; j++)
			if (!isdigit(arg[j])){
				printf("%s: Argument error.\n", args[0]);
				return -1;
			}
	}
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//                 ERROR RELATED WITH SIGNALS             
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void signalErrorHandler(){ perror("SIGNAL HANDLER INSTALL ERROR.\n"); }

void killSignalHandler(){ perror("SENDING SIGNAL ERROR.\n"); }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//                     ERROR RELATED WITH MUTEXES                     
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void mutexInitErrorHandler(int retval){
	printf("ERROR CREATING THE MUTEX.\n");
	if (retval == EAGAIN)
		printf("The system lacked the necessary resources (other than memory).\n");
	else if (retval == EPERM)
		printf("Privilege to perform the operation non existant.\n");
}

void mutexLockErrorHandler(int retval){
	printf("ERROR LOCKING THE MUTEX.\n");
	if (retval == EAGAIN)
		printf("TThe maximum number  of recursive locks for mutex has been exceeded.\n");
	else if (retval == ENOTRECOVERABLE)
		printf("The state protected by the mutex is not recoverable.\n");
	else if (retval == EDEADLK)
		printf("A deadlock condition was detected.\n");
}

void mutexUnlockErrorHandler(int retval){
	printf("ERROR UNLOCKING THE MUTEX.\n");
	if (retval == EPERM)
		printf("The current thread does not own the mutex.\n");
}

void mutexDestroyErrorHandler(){ perror("ERROR DESTROYING THE MUTEX\n"); }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//                   ERROR RELATED WITH SEMAPHORES           
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void semaphoreInitErrorHandler(){ perror("ERROR INITIATING THE SEMAPHORE\n"); }

void semaphoreWaitErrorHandler(){ perror("ERROR IN SEMAPHORE\n"); }

void semaphorePostErrorHandler(){ perror("ERROR IN SEMAPHORE\n"); }

void semaphoreDestroyErrorHandler(){ perror("ERROR DESTROYING THE SEMAPHORE\n"); }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//                   ERROR RELATED WITH THREADS           
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void pthreadCreateErrorHandler(int retval){
	printf("ERROR CREATING THE THREAD.\n");
	if (retval == EAGAIN)
		printf("Insufficient resources to create another thread..\n");
	else if (retval == EINVAL)
		printf("Invalid settings in attr.\n");
	else if (retval == EPERM)
		printf("Permission denied.\n");
}

void pthreadJoinErrorHandler(int retval){
	printf("ERROR JOINING THE THREAD.\n");
	if (retval == EAGAIN)
		printf("No thread could be found corresponding to the given TID.\n");
	else if (retval == EINVAL)
		printf("Another thread is already waiting on termination.\n");
	else if (retval == EDEADLK)
		printf("The given refers to the calling thread..\n");
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//              ERROR RELATED WITH CONDITION VARIABLES
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void condInitErrorHandler(int retval){
	printf("ERROR INITIATING THE CONDITIONAL VARIABLE.\n");
	if (retval == EAGAIN)
		printf("The system lacked the necessary resources (other than memory) to initialize another condition variable.\n");
}

void condWaitErrorHandler(int retval){
	printf("ERROR WAITING ON THE CONDITIONAL VARIABLE.\n");
	if (retval == EPERM)
		printf("The mutex type is PTHREAD_MUTEX_ERRORCHECK or the mutex is a robust mutex, and the current thread  does  not own the mutex.\n");
}

void condSignalErrorHandler(){ printf("ERROR SIGNALLING THE CONDITIONAL VARIABLE."); }

void condDestroyErrorHandler(){ printf("ERROR DESTROYING THE CONDITIONAL VARIABLE."); }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//                 ERROR RELATED WITH PROCESSES           
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void forkErrorHandler(){ perror("THE CREATION OF A SUB PROCESS WAS NOT EXECUTED."); }

void waitpidErrorHandler(){ perror("THERE WAS AN ERROR WAITING FOR A CHILD PROCESS."); }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//                 ERROR RELATED WITH FILES
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void openErrorHandler(){ perror("THERE WAS AN ERROR OPENING THE FILE / PIPE."); }

void mkfifoErrorHandler(){ perror("THERE WAS AN ERROR CREATING THE NAMED PIPE."); }

void writeErrorHandler(){ perror("ERROR WRITTING TO FILE / PIPE."); }

void readErrorHandler(){ perror("ERROR READING FROM FILE / PIPE."); }

void closeErrorHandler(){ perror("ERROR CLOSING THE FILE / PIPE."); }

void unlinkErrorHandler(){ perror("ERROR UNLINKING PIPE."); }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//                 ERROR RELATED WITH TIME
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void timeErrorHandler(){ perror("ERROR GETTING CURRENT TIME."); }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//                 ERROR RELATED WITH STRINGS
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void snprintfErrorHandler(){ printf("ERROR FORMATING THE STRING."); }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//                 ERROR RELATED WITH REDIRECTION
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void dup2ErrorHandler(){ perror("ERROR REDIRECTING THE INPUT / OUTPUT."); }