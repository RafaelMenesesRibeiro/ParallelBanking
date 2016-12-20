/*
// HEADER
// Accounts operations, version 4
// 2016/2017 - 1st Semestre
// Instituto Superior Tecnico
// U.C. Sistemas Operativos
// Rafael Ribeiro, nº 84758
*/

#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#define NUM_ACCOUNTS 	10
#define INTERESTRATE 	0.1
#define MAINTENANCE 	1

/*
 * Function:  accountInitialize 
 * -------------------------------------------------------------------
 *	Initializes all the accounts' balances to zero
 *
 *	return:		(void)
 */
void accountInitialize();

/*
 * Function:  accountExists
 * -------------------------------------------------------------------
 *	Checks if the account exists
 *
 *	accountID:	ID of the account to check
 *
 *	return:		(int) 0 if the account doesn't exist, 1 if it does
 */
int accountExists(int accountID);

/*
 * Function:  accountCharge
 * -------------------------------------------------------------------
 *	Removes money from the specified account
 *
 *	accountID:	ID of the account to remove money
 *	value:		value to be removed from the account
 *
 *	return:		(int) 0 if success, -1 if error
 */
int accountCharge(int accountID, int value);

/*
 * Function:  accountCredit 
 * -------------------------------------------------------------------
 *	Adds money to the specified account
 *
 *	accountID:	ID of the account to add money
 *	value:		value to be added to the account
 *
 *	return:		(int) 0 if success, -1 if error
 */
int accountCredit(int accountID, int value);

/*
 * Function:  accountReadBalance
 * -------------------------------------------------------------------
 *	Prints the specified account's balance
 *
 *	accountID:	ID of the account from which to read the balance
 *
 *	return:		(void)
 */
int accountReadBalance(int accountID);

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
int accountTransfer(int accountID1, int accountID2, int value);
/*
 * Function:  accountSimulate
 * -------------------------------------------------------------------
 *	Simulates the balance of all the accounts yearly for the specified time
 *
 *	numYears:	number of years to simulate
 *
 *	return:		(int) 0 if success, -1 if error
 */
int accountSimulation(int simYears);

/*
 * Function:  signalHandler
 * -------------------------------------------------------------------
 *	Changes the value of the Terminate global value so the simulation 
 *  stops  after the current year
 *
 *	return:		(void)
 */
void signalHandler();
 
/*
 * Function:  accountsEnd
 * -------------------------------------------------------------------
 *	Destroys the mutex
 *
 *	return:		(void)
 */
void accountsEnd();

#endif