/*
// FUNCTIONALITY
// Command Line Reader, version 3
// 2016/2017 - 1st Semestre
// Instituto Superior Tecnico
// U.C. Sistemas Operativos
// Rafael Ribeiro, nº 84758
*/

#include <stdio.h>
#include <string.h>
#include "comreader.h"

int readLineArguments(char **argVector, int vectorSize, char *buffer, int buffersize){
	int numtokens = 0, i;
	char *s = " \r\n\t";
	char *token;

	if (argVector == NULL || buffer == NULL || vectorSize <= 0 || buffersize <= 0)
		return 0;

	if (fgets(buffer, buffersize, stdin) == NULL)
		return -1;

	/* get the first token */
	token = strtok(buffer, s);

	/* walk through other tokens */
	while (numtokens < vectorSize - 1 && token != NULL ){
		argVector[numtokens] = token;
		numtokens++;
		token = strtok(NULL, s);
	}

	for (i = numtokens; i < vectorSize; i++)
		argVector[i] = NULL;

	return numtokens;
}

