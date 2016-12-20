/*
// HEADER
// Command Line Reader, version 3
// 2016/2017 - 1st Semestre
// Instituto Superior Tecnico
// U.C. Sistemas Operativos
// Rafael Ribeiro, nº 84758
*/

#ifndef COMREADER_H
#define COMREADER_H

/* 
Reads up to 'vectorSize' space-separated arguments from the standard input
and saves them in the entries of the 'argVector' argument.
This function returns once enough arguments are read or the end of the line 
is reached.

Arguments: 
	'argVector' should be a vector of char* previously allocated with
	as many entries as 'vectorSize'.
	'vectorSize' is the size of the above vector. A vector of size N allows up to 
	N-1 arguments to be read; the entry after the last argument is set to NULL.
	'buffer' is a buffer with 'buffersize' bytes, which will be 
	used to hold the strings of each argument.  

Return value:
	The number of arguments that were read, or -1 if some error occurred.
*/

int readLineArguments(char **argVector, int vectorSize, char *buffer, int buffersize);

#endif
