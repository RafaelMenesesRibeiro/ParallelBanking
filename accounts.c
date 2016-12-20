/*
// FUNCTIONALITY
// Accounts operations, version 4
// 2016/2017 - 1st Semestre
// Instituto Superior Tecnico
// U.C. Sistemas Operativos
// Rafael Ribeiro, nº 84758
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include "accounts.h"
#include "errorhandling.h"
#include "synchronization.h"

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a > b ? b : a)

//Declares the accounts vector.
int accountsBalances[NUM_ACCOUNTS];
//Declares the child process termination flag.
int simulationTerminate = 0;
//Defines a Mutex vector.
pthread_mutex_t accountsMutexesVector[NUM_ACCOUNTS];

void accountInitialize(){
	int i;
	for (i = 0; i < NUM_ACCOUNTS; i++) accountsBalances[i] = 0;
	for (i = 0; i < NUM_ACCOUNTS; i++) mutexInit(&accountsMutexesVector[i]);
}

int accountExists(int accountID){
	return (accountID > 0 && accountID <= NUM_ACCOUNTS);
}

int accountCharge(int accountID, int value){
	if (!accountExists(accountID)) return -1;
	mutexLock(&accountsMutexesVector[accountID - 1]);
	if (accountsBalances[accountID - 1] < value){
		mutexUnlock(&accountsMutexesVector[accountID - 1]);
		return -1;
	}
	accountsBalances[accountID - 1] -= value;
	mutexUnlock(&accountsMutexesVector[accountID - 1]);
	return 0;
}

int accountCredit(int accountID, int value){
	if (!accountExists(accountID) || value < 0) return -1;
	mutexLock(&accountsMutexesVector[accountID - 1]);
	accountsBalances[accountID - 1] += value;
	mutexUnlock(&accountsMutexesVector[accountID - 1]);
	return 0;
}

int accountReadBalance(int accountID){
	if (!accountExists(accountID)) return -1;
	mutexLock(&accountsMutexesVector[accountID - 1]);
	int balance = accountsBalances[accountID - 1];
	mutexUnlock(&accountsMutexesVector[accountID - 1]);
	return balance;
}

int accountTransfer(int accountID1, int accountID2, int value){
	if (!accountExists(accountID1) || !accountExists(accountID2) || accountID1 == accountID2) return -1;
	int max = MAX(accountID1, accountID2);
	int min = MIN(accountID1, accountID2);
	mutexLock(&accountsMutexesVector[min - 1]);
	mutexLock(&accountsMutexesVector[max - 1]);
	if (accountsBalances[accountID1 - 1] < value){
		mutexUnlock(&accountsMutexesVector[accountID1 - 1]);
		mutexUnlock(&accountsMutexesVector[accountID2 - 1]);
		return -1;
	}
	accountsBalances[accountID1 - 1] -= value;
	accountsBalances[accountID2 - 1] += value;
	mutexUnlock(&accountsMutexesVector[max - 1]);
	mutexUnlock(&accountsMutexesVector[min - 1]);
	return 0;	
}

int accountSimulation(int simYears){
	int i, simYear;
	for (simYear = 0; simYear <= simYears && !simulationTerminate; simYear++){
		printf("SIMULATION:\t      Year %3d\n==============================\n",  simYear);
		for (i = 0; i < NUM_ACCOUNTS; i++){
			if (simYear != 0)
				accountCredit(i + 1, MAX(accountReadBalance(i + 1) * INTERESTRATE - MAINTENANCE, 0));
			while (printf("Account %3d: \tBalance %6d\n", i + 1, accountReadBalance(i + 1))) {
        		if (errno == EINTR)
          			continue;
        		else
          			break;
      		}
		}
		printf("\n");
	}
	if (simulationTerminate) return 1;
	else return 0;
}

void accountsEnd(){
	int i;
	for (i = 0; i < NUM_ACCOUNTS; i++) mutexDestroy(&accountsMutexesVector[i]);
}

void signalHandler(){
	simulationTerminate = 1;
}