/*
// FUNCTIONALITY
// Structures, version 4
// 2016/2017 - 1st Semestre
// Instituto Superior Tecnico
// U.C. Sistemas Operativos
// Rafael Ribeiro, nº 84758
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structure.h"
#include "errorhandling.h"

char* commandToString(commandStruct commStruct){
	long unsigned int len = sizeof(int) * 3 + 32;
	static char aux[sizeof(int) * 3 + 32];
	switch(commStruct.command){
	case -1:
		return "Terminating Thread";
	case 0:
		if (snprintf(aux, len, "%s(%d, %d)\n", _CHARGE, commStruct.accountID1, commStruct.value) < 0) {snprintfErrorHandler(); return "ERROR"; }
		break;
	case 1:
		if (snprintf(aux, len, "%s(%d, %d)\n", _CREDIT, commStruct.accountID1, commStruct.value) < 0) {snprintfErrorHandler(); return "ERROR"; }
		break;
	case 2:
		if (snprintf(aux, len, "%s(%d)\n", _READBALANCE, commStruct.accountID1) < 0) {snprintfErrorHandler(); return "ERROR"; }
		break;
	case 3:
		if (snprintf(aux, len, "%s(%d, %d, %d)\n", _TRANSFER, commStruct.accountID1, commStruct.accountID2, commStruct.value) < 0) {snprintfErrorHandler(); return "ERROR"; }
		break;
	case 4:
		if (snprintf(aux, len, "%s(%d)\n", _SIMULATE, commStruct.value) < 0) {snprintfErrorHandler(); return "ERROR"; }
		break;
	case 5:
		if (snprintf(aux, len, "%s\n", _EXIT) < 0) {snprintfErrorHandler(); return "ERROR"; }
		break;
	case 6:
		if (snprintf(aux, len, "%s %s\n", _EXIT, _NOWVARIANT) < 0) {snprintfErrorHandler(); return "ERROR"; }
		break;
	default:
		if (snprintf(aux, len, "Error while parsing the structure.\n") < 0) {snprintfErrorHandler(); return "ERROR"; }
	}
	return aux;
}