/*
// FUNCTIONALITY
// File Manager, version 4
// 2016/2017 - 1st Semestre
// Instituto Superior Tecnico
// U.C. Sistemas Operativos
// Rafael Ribeiro, nº 84758
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include "filemanager.h"
#include "errorhandling.h"

int makeFIFO(char *name){
	if ((mkfifo(name, 0777) == -1)) { mkfifoErrorHandler(); exit(EXIT_FAILURE); }
	return 1;
}

void makeOutputFIFO(char *name){ makeFIFO(name); }

int makeopenMainFIFO(){
	int i;
	char *fifo1 = "i-banco-pipe";
	char *fifo2 = "/tmp/i-banco-pipe";
	if ((mkfifo(fifo1, 0777) == -1)){
		if (errno == EACCES){
			makeFIFO(fifo2);
			i = fileOpen(fifo2, O_RDONLY);
		}
		else { mkfifoErrorHandler(); exit(EXIT_FAILURE); }
	}
	else i = fileOpen(fifo1, O_RDONLY);
	return i;
}

int fileOpen(char *name, int flag){
	int i;
	if ((i = open(name, flag)) == -1) { openErrorHandler(); exit(EXIT_FAILURE); }
	return i;
}

void fileRead(int fd, void *pointer, int size){
	if (read(fd, pointer, size) == -1) { readErrorHandler(); exit(EXIT_FAILURE); }
}

void fileWrite(int fd, void *pointer, int size){
	if (write(fd, pointer, size) == -1) { writeErrorHandler(); exit(EXIT_FAILURE); }	
}

void fileClose(int fd){ if (close(fd) == -1) { closeErrorHandler(); exit(EXIT_FAILURE); }}

int fileDup(int fd){
	int i;
	if ((i = dup(fd)) == -1) { dup2ErrorHandler(); exit(EXIT_FAILURE); }
	return i;
}

void fileDup2(int newFd, int oldFd){
	if (dup2(newFd, oldFd) == -1) { dup2ErrorHandler(); exit(EXIT_FAILURE); }
}

void fileUnlink(char *name){
	if (unlink(name) == -1){ unlinkErrorHandler(); exit(EXIT_FAILURE); }
}