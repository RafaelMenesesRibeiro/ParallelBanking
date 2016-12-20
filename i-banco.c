/*
// FUNCTIONALITY
// SO Project, version 4, exercise 4
// 2016/2017 - 1st Semestre
// Instituto Superior Tecnico
// U.C. Sistemas Operativos
// Rafael Ribeiro, nº 84758
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include "i-banco.h"
#include "thread.h"
#include "accounts.h"
#include "errorhandling.h"
#include "filemanager.h"

//Vector that stores the PIDs of the create sub processes.
int childProcID[MAXSONS];
//Variable that stores the max number of processes the program can create.
int numChildProc = 0;
//Variable that stores the file descriptor for the Pipe.
int fdBank = 0;

int main(int argc, char** argv){
	//Assigns the signalHandler function as a signal handler function
	//for SIGUSR1 signal.
	if (signal(SIGUSR1, signalHandler) == SIG_ERR) signalErrorHandler();

	//Calls the accountInitialize function from accounts.c that initializes all
	//accounts' balances to 0.
	accountInitialize();
	threadInitialize();

	int fdBank = makeopenMainFIFO();

	while(1){
		terminalStruct termStruct;
		fileRead(fdBank, &termStruct, sizeof(terminalStruct));
		/*
		terminalStruct *termStructP;
		fileRead(fdBank, termStructP, sizeof(terminalStruct));
		terminalStruct termStruct = *termStructP;
		*/

		switch(termStruct.commStruct.command){
			case -1:
			case 0:
			case 1:
			case 2:
			case 3:
				threadProduce(termStruct);
				break;
			case 4:
				startSimulation(termStruct.commStruct.value);
				break;
			case 5:
				commandExitNormal();
				break;
			case 6:
				commandExitNow();
				break;
		}
	}
	fileClose(fdBank);
}

void commandCharge(int accountID, int value){
	if (accountCharge(accountID, value) == -1) 
		valueErrorMsg(_CHARGE, accountID, value);
	else printf("%s(%d, %d): OK\n", _CHARGE, accountID, value);
}

void commandCredit(int accountID, int value){
	if (accountCredit(accountID, value) == -1)
		valueErrorMsg(_CREDIT, accountID, value);
	else printf("%s(%d, %d): OK\n", _CREDIT, accountID, value);
}

void commandReadBalance(int accountID){
	int balance = accountReadBalance(accountID);
	if (balance == -1)
		valueErrorMsg(_READBALANCE, accountID, balance);
	else printf("%s(%d): O saldo atual é %d.\n", _READBALANCE, accountID, balance);
}

void commandTransfer(int accountID1, int accountID2, int value){
	if (accountTransfer(accountID1, accountID2, value) == -1)
		printf("Erro ao transferir valor da conta %d para a conta %d.\n", accountID1, accountID2);
	else printf("transferir(%d, %d, %d): OK\n", accountID1, accountID2, value);
}

void startSimulation(int numYears){
	threadComunicate(numYears);
}

void commandSimulate(int numYears){
	if (numChildProc >= MAXSONS){
		printf("simular: ERROR. Max number of simulations executed.\n");
		return;
	}
	//Creates a sub process which only function is to run the simulation.
	int sPID = fork();
	
	//fork() didn't work.
	if (sPID == -1){
		forkErrorHandler();
		return;
	}
	//fork() works and a child process is created.
	//The sub process calls the function. If it returns an error value,
	//the process exits with -1.
	else if (sPID == 0){
		int fd;
		unsigned int len;
		/*
		Declares and calculates the maximum lenght of the string filename.
		String filename: "i-banco-sim" + PID + ".txt" (16 + 1 + length of PID)
		sizeof(pid_t) gets the maximum lenght of a PID in the system that is
		running the program.
		*/
		len = sizeof(pid_t) + 17 + 1;
		char filename[len];
		snprintf(filename, len, "i-banco-sim-%u.txt", getpid());

		if ((fd = open(filename, O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU|S_IRWXG|S_IRWXO)) == -1) { openErrorHandler(); exit(EXIT_FAILURE); }
		fileDup2(fd, fileno(stdout));
		int returnvalue = accountSimulation(numYears);
		fileDup2(fileno(stdout), fd);
		fileClose(fd);

		if (returnvalue == 0) exit(0);
		else if (returnvalue == 1) exit(1);
	}
	//The main process adds the sub process's ID to the childProcID vector
	//and increases the number of global processes created.	
	else childProcID[(numChildProc)++] = sPID;
}

void commandExitNow(){
	//Sends the SIGUSR1 signal (attributed to the signalHandler function) to stop
	//all sub processes as soon as they finish the current year's simulation.
	for (int i = 0; i < numChildProc; i++)
		if (kill(childProcID[i], SIGUSR1) == -1)
			printf("kill: Error at sending a signal to process. PID = %d\n", childProcID[i]);
	//Calls the commandExitNormal function to print all the sub processes' IDs
	//and correspondent exit status.
	commandExitNormal();
	exit(EXIT_FAILURE);
}

void commandExitNormal(){
	int sPID, stateSon;
	printf("\n==============================\n");
	printf("I-BANK is terminating.\n--\n");
	//Waits for every sub process created (which PIDs are stored in the
	//childProcID vector) to terminate (as soon as they finish the full
	//simulation).
	for (int i = 0; i < numChildProc; i++){
		sPID = waitpid(childProcID[i], &stateSon, 0);
		//waitpid() didn't work.
		if (sPID == -1) waitpidErrorHandler();
		//waitpid() worked.
		else if (WIFEXITED(stateSon)){
			//The process ended by "sair agora" input.
			if (WEXITSTATUS(stateSon) == 1) 
				printf("SIGNAL TERMINATED PROCESS.\n");
			//The process ended normally. Both "sair" and "sair agora".
			printf("SUB-PROCESS TERMINATED (PID = %d; NORMAL TERMINATION)\n", sPID);
		}
		//The process ended by signal.
		//(Abruptly. Ex: trough shell command kill -KILL <PID>
		else if (!WIFEXITED(stateSon) && WIFSIGNALED(stateSon)){
			printf("SUB-PROCESS TERMINATED (PID = %d; ABRUPT TERMINATION)\n", sPID);
		}
	}
	//Calls the functions that terminate and destroy all create assets
	//declared troughout the execution of this program (that aren't
	//destroyed automaticly).
	threadEnd();
	accountsEnd();
	printf("--\nI-BANK terminated.\n");
	printf("==============================\n\n");
	exit(EXIT_SUCCESS);
}