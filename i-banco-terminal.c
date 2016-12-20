/*
// FUNCTIONALITY
// Pipe Operations, version 4
// 2016/2017 - 1st Semestre
// Instituto Superior Tecnico
// U.C. Sistemas Operativos
// Rafael Ribeiro, nº 84758
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include "i-banco-terminal.h"
#include "comreader.h"
#include "errorhandling.h"
#include "structure.h"
#include "filemanager.h"

//Defines to improve code perception.
#define COMMAND(a) !strcmp(args[0], a)
#define VARIANT(a) !strcmp(args[1], a)

//Variables that store the file descriptors for the Pipes.
int fdCommandSend = 0;
int fdCommandReturn = 0;
//Variables that store the times at with a command was started and ended.
time_t timeCommandInit;
time_t timeCommandCompleted;
double timeInterval;
//Structure that holds the last sent command
commandStruct commStruct;
int main(int argc, char** argv){
	char *pathname = argv[1];
	char *args[MAXARGS + 1];
	char buffer[BUFFER_SIZE];
	int len;
	
	if (signal(SIGUSR1, signalHandler1) == SIG_ERR) signalErrorHandler();
	if (signal(SIGPIPE, signalHandler2) == SIG_ERR) signalErrorHandler();


	fdCommandSend = fileOpen(pathname, O_WRONLY);
	
	len = sizeof(pid_t) + 16;
	char pipeOutput[len];
	snprintf(pipeOutput, len, "i-banco-pipe-%u", getpid());
	makeOutputFIFO(pipeOutput);
	if ((fdCommandReturn = open(pipeOutput, O_RDONLY|O_NONBLOCK)) == -1) { openErrorHandler(); exit(EXIT_FAILURE); }

	printf("==============================\n");
	printf("WELCOME TO I-BANK\n");
	printf("==============================\n\n");

	while (1){
		int argNum;
		//Reads the arguments in the input.
		argNum = readLineArguments(args, MAXARGS + 1, buffer, BUFFER_SIZE);

		//EOF
		if (argNum < 0) exit(EXIT_SUCCESS);
		//No arguments (empty line)
		if (argNum == 0) continue;
		//Charge
		else if (COMMAND(_CHARGE)){
			if (argNum != 3) syntaxErrorMsg(_CHARGE);
			else if (!checkIsValid(2, args))
				terminalDo(COMMAND_CHARGE, atoi(args[1]), -1, atoi(args[2]));
		}
		//Credit
		else if (COMMAND(_CREDIT)){
			if (argNum != 3) syntaxErrorMsg(_CREDIT);
			else if (!checkIsValid(2, args))
				terminalDo(COMMAND_CREDIT, atoi(args[1]), -1, atoi(args[2]));
		}
		//Read balance
		else if (COMMAND(_READBALANCE)){
			if (argNum != 2) syntaxErrorMsg(_READBALANCE);
			else if (!checkIsValid(1, args))
				terminalDo(COMMAND_READBALANCE, atoi(args[1]), -1, -1);
		}
		//Transfer
		else if (COMMAND(_TRANSFER)){
			if (argNum != 4) syntaxErrorMsg(_TRANSFER);
			else if (!checkIsValid(3, args))
				terminalDo(COMMAND_TRANSFER, atoi(args[1]), atoi(args[2]), atoi(args[3]));
		}
		//Simulate
		else if (COMMAND(_SIMULATE)){
			if (argNum != 2) syntaxErrorMsg(_SIMULATE);
			else if (!checkIsValid(1, args))
				terminalDo(COMMAND_SIMULATE, -1, -1, atoi(args[1]));
		}
		//Exit
		else if (COMMAND(_EXIT)){
			//Normal exit
			if (argNum == 1)
				terminalDo(COMMAND_EXIT, -1, -1, -1);
			//Exit now
			else if (argNum == 2 && args[1] && VARIANT(_NOWVARIANT))
				terminalDo(COMMAND_EXITNOW, -1, -1, -1);
			else syntaxErrorMsg(_EXIT);
		}
		//Exit terminal
		else if (COMMAND(_EXITTERMINAL)){
			if (argNum != 1) syntaxErrorMsg(_EXITTERMINAL);
			else{
				fileClose(fdCommandSend);
				fileClose(fdCommandReturn);
				fileUnlink(pipeOutput);
				exit(EXIT_SUCCESS);
			}
		}
		//Unrecognized input
		else
			printf("%s: ERROR. Unknown command.\n\n", args[0]);
	}
	exit(EXIT_FAILURE);
}

void terminalDo(int c, int ID1, int ID2, int v){
	terminalSendCommand(c, ID1, ID2, v);
	if (c != 4 && c != 5 && c != 6){
		terminalStartClock();
		pause();
	}
}

void terminalSendCommand(int c, int ID1, int ID2, int v){
	commandStruct aux = {.command = c, .accountID1 = ID1, .accountID2 = ID2, .value = v};
	commStruct = aux;
	terminalStruct termStruct = {.commStruct = commStruct, .PID = getpid()};
	terminalStruct *termStructP = &termStruct;
	fileWrite(fdCommandSend, termStructP, sizeof(terminalStruct));
}

void terminalStartClock(){
	if (time(&timeCommandInit) == -1) { timeErrorHandler(); exit(EXIT_FAILURE); }
}

void terminalPrintOutput(){
	char buffer = ' ';
	while(buffer != '\n'){
		fileRead(fdCommandReturn, &buffer, sizeof(char));
		printf("%c", buffer);
	}
}

void terminalPrintTime(){
	timeInterval = (double) difftime(timeCommandCompleted, timeCommandInit);
	printf("Time: %f \t Command: %s\n", timeInterval, commandToString(commStruct));
}

void signalHandler1(){
	if (time(&timeCommandCompleted) == -1) {timeErrorHandler(); exit(EXIT_FAILURE); }
	terminalPrintOutput();
	terminalPrintTime();
}

void signalHandler2(){
	char *text = "THE PIPE WAS CLOSE. TERMINATING.\n";
	fileWrite(fileno(stdout), text, strlen(text));
	exit(EXIT_FAILURE);
}