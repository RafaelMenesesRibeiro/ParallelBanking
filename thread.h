/*
// FUNCTIONALITY
// Threads, version 4
// 2016/2017 - 1st Semestre
// Instituto Superior Tecnico
// U.C. Sistemas Operativos
// Rafael Ribeiro, nº 84758
*/

#ifndef THREADS_H
#define THREADS_H

#include "structure.h"

#define NUM_TRABALHADORAS	3
#define CMD_BUFFER_DIM	(NUM_TRABALHADORAS * 2)

/*
//Structure that defines a command to be run.
typedef struct{
	int command;
	int accountID1;
	int accountID2;
	int value;
} commandStruct;
*/

/*
 * Function:  threadInitialize 
 * -------------------------------------------------------------------
 *	Initializes all the threads and all the related objects.
 *
 *	return:		(void)
 */
void threadInitialize();

/*
 * Function:  threadProduce
 * -------------------------------------------------------------------
 *	Writes the given information on the buffer.
 *
 *	struc:		structure
 *
 *	return:		(void)
 */
void threadProduce(terminalStruct struc);

/*
 * Function: threadConsume
 * -------------------------------------------------------------------
 * Based on the structure given as arguement, decides what the thread
 * is going to execute.
 *
 *	param:		pointer to a structure that defines a task
 *
 *	return:		(void)
 */
void *threadConsume(void *param);

/*
 * Function: threadComunicate
 * -------------------------------------------------------------------
 * Checks if the conditions for a simulation to execute are present.
 *
 *	numYears:	number of years to simulate
 *
 *	return:		(void)
 */
void threadComunicate(int numYears);

/*
 * Function: threadWriteLog
 * -------------------------------------------------------------------
 * Writes the commands and respective arguments to the log file.
 *
 *	structure:	structure composed of a command and it's arguments
 *
 *	return:		(void)
 */
int threadWriteToLog(commandStruct structure);

/*
 * Function:  cleanHouse
 * -------------------------------------------------------------------
 *	Destroys the threads auxiliar objects.
 *
 *	return:		(void)
 */
void threadEnd();

#endif