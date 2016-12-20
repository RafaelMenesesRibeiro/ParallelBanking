/*
// HEADER
// Structures, version 4
// 2016/2017 - 1st Semestre
// Instituto Superior Tecnico
// U.C. Sistemas Operativos
// Rafael Ribeiro, nº 84758
*/
#ifndef STRUCTURE_H
#define STRUCTURE_H

//Structure that defines a command to be run.
typedef struct{
	int command;
	int accountID1;
	int accountID2;
	int value;
} commandStruct;

typedef struct{
	commandStruct commStruct;
	int PID;
} terminalStruct;

#define COMMAND_TERMINATE	-1
#define COMMAND_CHARGE	0
#define COMMAND_CREDIT	1
#define COMMAND_READBALANCE	2
#define COMMAND_TRANSFER	3
#define COMMAND_SIMULATE 4
#define COMMAND_EXIT	5
#define COMMAND_EXITNOW 6

#define _CHARGE 		"debitar"
#define _CREDIT 		"creditar"
#define _READBALANCE 	"lerSaldo"
#define _TRANSFER		"transferir"
#define _SIMULATE 		"simular"
#define _EXIT 			"sair"
#define _NOWVARIANT		"agora"
#define _EXITTERMINAL	"sair-terminal"

/*
 * Function: commandToString
 * -------------------------------------------------------------------
 *	Translates the commandStruct to a String.	
 *
 *	commStruct:	structure to represent as String
 *
 *	return:		(char*) String that represents the commandStruct
 */
char* commandToString(commandStruct commStruct);

#endif