/*
// HEADER
// SO Project, version 4, exercise 4
// 2016/2017 - 1st Semestre
// Instituto Superior Tecnico
// U.C. Sistemas Operativos
// Rafael Ribeiro, nº 84758
*/

#ifndef IBANCO_H
#define IBANCO_H

#define MAXSONS 		20

/*
 * Function:  commandCharge
 * -------------------------------------------------------------------
 *	Removes money from the specified account
 *
 *	accountID:	ID of the account from which to remove money
 *	value:		value to be removed from the account
 *
 *	return:		(void)
 */
void commandCharge(int accountID, int value);

/*
 * Function:  commandCredit 
 * -------------------------------------------------------------------
 *	Adds money to the specified account
 *
 *	accountID:	ID of the account to which to add money
 *	value:		value to be added to the account
 *
 *	return:		(void)
 */
void commandCredit(int accountID, int value);

/*
 * Function:  commandReadBalance
 * -------------------------------------------------------------------
 *	Prints the specified account's balance
 *
 *	accountID:	ID of the account from which to read the balance
 *
 *	return:		(void)
 */
void commandReadBalance(int accountID);

/*
 * Function:  commandTransfer
 * -------------------------------------------------------------------
 *	Transfers money
 *
 *	accountID1:	ID of the account from which to remove the money
 *	accountID2:	ID of the account to wich to add money
 *	value:		value to be transfered
 *
 *	return:		(void)
 */
void commandTransfer(int accountID1, int accountID2, int value);

/* 
 * Function:  startSimulation
 * -------------------------------------------------------------------
 *	Verifies if it's possible to simulate
 *
 *	numYears:	number of years to simulate
 *
 *	return:		(void)
 */
void startSimulation(int numYears);

/*
 * Function:  commandSimulate
 * -------------------------------------------------------------------
 *	Simulates the balance of all the accounts yearly for the specified time
 *
 *	numYears:	number of years to simulate
 *
 *	return:		(void)
 */
void commandSimulate(int numYears);

/*
 * Function:  commandExitNow
 * -------------------------------------------------------------------
 *	Exits all the processes after they finish the current simulation year
 *	Exits main process
 *
 *	return:		(void)
 */
void commandExitNow();

/*
 * Function:  commandExitNormal
 * -------------------------------------------------------------------
 *	Exits all the processes after finish the entire simulation
 *	Exits main process
 *
 *	return:		(void)
 */
void commandExitNormal();

#endif