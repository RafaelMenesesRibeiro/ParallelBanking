/*
// HEADER
// Terminal, version 4, exercise 4
// 2016/2017 - 1st Semestre
// Instituto Superior Tecnico
// U.C. Sistemas Operativos
// Rafael Ribeiro, nº 84758
*/

#ifndef IBANCOTERMINAL_H
#define IBANCOTERMINAL_H

#define MAXARGS 		4
#define BUFFER_SIZE 	100

/*
 * Function:  terminalDo
 * -----------------------------------------------------------------------------
 *	Sends the command and prints the output.
 *
 *	c:			command code
 *	ID1:		account to operate
 *	ID2:		account to operate
 *	v:			value
 *
 *	return:		(void)
 */
void terminalDo(int c, int ID1, int ID2, int v);

/*
 * Function:  terminalSendCommand
 * -----------------------------------------------------------------------------
 *	Sends the command.
 *
 *	c:			command code
 *	ID1:		account to operate
 *	ID2:		account to operate
 *	v:			value
 *
 *	return:		(void)
 */
void terminalSendCommand(int c, int ID1, int ID2, int v);

/*
 * Function:  terminalStartClock
 * -----------------------------------------------------------------------------
 *	Starts counting the execution time of the sent command.
 *
 *	return:		(void)
 */
void terminalStartClock();

/*
 * Function:  terminalPrintOutput
 * -----------------------------------------------------------------------------
 *	Prints the output of the sent command.
 *
 *	return:		(void)
 */
void terminalPrintOutput();

/*
 * Function:  terminalPrintTime
 * -----------------------------------------------------------------------------
 *	Prints the time that took the command to be executed.
 *
 *	return:		(void)
 */
void terminalPrintTime();

/*
 * Function:  signalHandler1
 * -----------------------------------------------------------------------------
 *	Sets the value of timeCommandCompleted to the current clock time.
 *
 *	return:		(void)
 */
void signalHandler1();

/*
 * Function:  signalHandler2
 * -----------------------------------------------------------------------------
 *	Terminates the program because the pipe to send commands was closed.
 *
 *	return:		(void)
 */
void signalHandler2();

#endif