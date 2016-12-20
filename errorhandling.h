/*
// HEADER
// Error handling, version 3
// 2016/2017 - 1st Semestre
// Instituto Superior Tecnico
// U.C. Sistemas Operativos
// Rafael Ribeiro, nº 84758
*/

#ifndef ERRORHANDLING_H
#define ERRORHANDLING_H

/*
 * Function: syntaxErrorMsg
 * -------------------------------------------------------------------
 *	Prints an error message. (error related with syntax)
 *
 *	command:	command that lead to the error
 *
 *	return:		(void)
 */
void syntaxErrorMsg(char command[]);

/*
 * Function: valueErrorMsg
 * -------------------------------------------------------------------
 *	Prints an error message. (error related with input value)
 *
 *	command:	command that lead to the error
 *
 *	return:		(void)
 */
void valueErrorMsg(char command[], int accountID, int value);

/*
 * Function: checkIsValid
 * -------------------------------------------------------------------
 *	Checks if the given strings are valid integer arguments
 *
 *	argNum:		number of arguments to check
 *	**args:		vector of arguments to check
 *
 *	return:		(int) -1 if error, 0 if not
 */
int checkIsValid(int argNum, char **args);

// -------------------------------------------------------------------
// -------------------------------------------------------------------
//                 ERROR RELATED WITH SIGNALS             
// -------------------------------------------------------------------
// -------------------------------------------------------------------
/*
 * Function:  signalErrorHandler
 * -------------------------------------------------------------------
 *	Prints a specific error message for an error caused by
 *  signal.
 *
 *	return:		(void)
 */
void signalErrorHandler();

/*
 * Function:  killSignalHandler
 * -------------------------------------------------------------------
 *	Prints a specific error message for an error caused by
 *  kill.
 *
 *	return:		(void)
 */
void killSignalHandler();

// -------------------------------------------------------------------
// -------------------------------------------------------------------
//                     ERROR RELATED WITH MUTEXES                     
// -------------------------------------------------------------------
// -------------------------------------------------------------------
/*
 * Function:  mutexInitErrorHandler
 * -------------------------------------------------------------------
 *	Prints a specific error message for an error caused by
 *  pthread_mutex_init.
 *
 *	retval:		value to indicate the error
 *
 *	return:		(void)
 */
void mutexInitErrorHandler(int retval);

/*
 * Function:  mutexLockErrorHandler
 * -------------------------------------------------------------------
 *	Prints a specific error message for an error caused by
 *  pthread_mutex_lock.
 *
 *	retval:		value to indicate the error
 *
 *	return:		(void)
 */
void mutexLockErrorHandler(int retval);

/*
 * Function:  mutexUnlockErrorHandler
 * -------------------------------------------------------------------
 *	Prints a specific error message for an error caused by
 *  pthread_mutex_unlock.
 *
 *	retval:		value to indicate the error
 *
 *	return:		(void)
 */
void mutexUnlockErrorHandler(int retval);

/*
 * Function:  mutexDestroyErrorHandler
 * -------------------------------------------------------------------
 *	Prints a specific error message for an error caused by
 *  pthread_mutex_destroy.
 *
 *	return:		(void)
 */
void mutexDestroyErrorHandler();

// -------------------------------------------------------------------
// -------------------------------------------------------------------
//                   ERROR RELATED WITH SEMAPHORES           
// -------------------------------------------------------------------
// -------------------------------------------------------------------

/*
 * Function:  semaphoreInitErrorHandler
 * -------------------------------------------------------------------
 *	Prints a specific error message for an error caused by
 *  sem_init.
 *
 *	return:		(void)
 */
void semaphoreInitErrorHandler();

/*
 * Function:  semaphoreWaitErrorHandler
 * -------------------------------------------------------------------
 *	Prints a specific error message for an error caused by
 *  sem_wait.
 *
 *	return:		(void)
 */
void semaphoreWaitErrorHandler();

/*
 * Function:  semaphorePostErrorHandler
 * -------------------------------------------------------------------
 *	Prints a specific error message for an error caused by
 *  sem_post.
 *
 *	return:		(void)
 */
void semaphorePostErrorHandler();

/*
 * Function:  semaphoreDestroyErrorHandler
 * -------------------------------------------------------------------
 *	Prints a specific error message for an error caused by
 *  sem_destroy.
 *
 *	return:		(void)
 */
void semaphoreDestroyErrorHandler();

// -------------------------------------------------------------------
// -------------------------------------------------------------------
//                   ERROR RELATED WITH THREADS           
// -------------------------------------------------------------------
// -------------------------------------------------------------------
/*
 * Function:  pthreadCreateErrorHandler
 * -------------------------------------------------------------------
 *	Prints a specific error message for an error caused by
 *  pthread_create.
 *
 *	retval:		value to indicate the error
 *
 *	return:		(void)
 */
void pthreadCreateErrorHandler(int retval);

/*
 * Function:  pthreadJoinErrorHandler
 * -------------------------------------------------------------------
 *	Prints a specific error message for an error caused by
 *  pthread_join.
 *
 *	retval:		value to indicate the error
 *
 *	return:		(void)
 */
void pthreadJoinErrorHandler(int retval);

// -------------------------------------------------------------------
// -------------------------------------------------------------------
//              ERROR RELATED WITH CONDITION VARIABLES
// -------------------------------------------------------------------
// -------------------------------------------------------------------
/*
 * Function:  condInitErrorHandler
 * -------------------------------------------------------------------
 *	Prints a specific error message for an error caused by
 *  pthread_cond_init.
 *
 *	retval:		value to indicate the error
 *
 *	return:		(void)
 */
void condInitErrorHandler(int retval);

/*
 * Function:  condWaitErrorHandler
 * -------------------------------------------------------------------
 *	Prints a specific error message for an error caused by
 *  pthread_cond_wait.
 *
 *	retval:		value to indicate the error
 *
 *	return:		(void)
 */
void condWaitErrorHandler(int retval);

/*
 * Function:  condSignalErrorHandler
 * -------------------------------------------------------------------
 *	Prints a specific error message for an error caused by
 *  pthread_cond_signal.
 *
 *	return:		(void)
 */
void condSignalErrorHandler();

/*
 * Function:  condDestroyErrorHandler
 * -------------------------------------------------------------------
 *	Prints a specific error message for an error caused by
 *  pthread_cond_destroy.
 *
 *	return:		(void)
 */
void condDestroyErrorHandler();

// -------------------------------------------------------------------
// -------------------------------------------------------------------
//                   ERROR RELATED WITH PROCESSES           
// -------------------------------------------------------------------
// -------------------------------------------------------------------
/*
 * Function:  forkErrorHandler
 * -------------------------------------------------------------------
 *	Prints a specific error message for an error caused by
 *  fork.
 *
 *	return:		(void)
 */
void forkErrorHandler();

/*
 * Function:  waitpidErrorHandler
 * -------------------------------------------------------------------
 *	Prints a specific error message for an error caused by
 *  waitpid.
 *
 *	return:		(void)
 */
void waitpidErrorHandler();

// -------------------------------------------------------------------
// -------------------------------------------------------------------
//                 ERROR RELATED WITH FILES
// -------------------------------------------------------------------
// -------------------------------------------------------------------
/*
 * Function:  openErrorHandler
 * -------------------------------------------------------------------
 *	Prints a specific error message for an error caused by
 *  open.
 *
 *	return:		(void)
 */
void openErrorHandler();

/*
 * Function:  mkfifoErrorHandler
 * -------------------------------------------------------------------
 *	Prints a specific error message for an error caused by
 *  mkfifo.
 *
 *	return:		(void)
 */
void mkfifoErrorHandler();

/*
 * Function:  writeErrorHandler
 * -------------------------------------------------------------------
 *	Prints a specific error message for an error caused by
 *  write.
 *
 *	return:		(void)
 */
void writeErrorHandler();

/*
 * Function:  readErrorHandler
 * -------------------------------------------------------------------
 *	Prints a specific error message for an error caused by
 *  read.
 *
 *	return:		(void)
 */
void readErrorHandler();

/*
 * Function:  closeErrorHandler
 * -------------------------------------------------------------------
 *	Prints a specific error message for an error caused by
 *  close.
 *
 *	return:		(void)
 */
void closeErrorHandler();

/*
 * Function:  unlinkErrorHandler
 * -------------------------------------------------------------------
 *	Prints a specific error message for an error caused by
 *  unlink.
 *
 *	return:		(void)
 */
void unlinkErrorHandler();

// -------------------------------------------------------------------
// -------------------------------------------------------------------
//                 ERROR RELATED WITH TIME
// -------------------------------------------------------------------
// -------------------------------------------------------------------
/*
 * Function:  timeErrorHandler
 * -------------------------------------------------------------------
 *	Prints a specific error message for an error caused by
 *  time.
 *
 *	return:		(void)
 */
void timeErrorHandler();

// -------------------------------------------------------------------
// -------------------------------------------------------------------
//                 ERROR RELATED WITH STRINGS
// -------------------------------------------------------------------
// -------------------------------------------------------------------
/*
 * Function:  snprintfErrorHandler
 * -------------------------------------------------------------------
 *	Prints a specific error message for an error caused by
 *  snprintf.
 *
 *	return:		(void)
 */
void snprintfErrorHandler();

// -------------------------------------------------------------------
// -------------------------------------------------------------------
//                 ERROR RELATED WITH REDIRECTION
// -------------------------------------------------------------------
// -------------------------------------------------------------------
/*
 * Function:  dup2ErrorHandler
 * -------------------------------------------------------------------
 *	Prints a specific error message for an error caused by
 *  dup2.
 *
 *	return:		(void)
 */
void dup2ErrorHandler();

#endif