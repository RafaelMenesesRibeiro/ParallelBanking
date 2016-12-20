/*
// HEADER
// File Manager, version 4
// 2016/2017 - 1st Semestre
// Instituto Superior Tecnico
// U.C. Sistemas Operativos
// Rafael Ribeiro, nº 84758
*/
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

int makeFIFO(char *name);

void makeOutputFIFO(char *name);

int makeopenMainFIFO();

int fileOpen(char *name, int flag);

void fileClose(int fd);

void fileRead(int fd, void *pointer, int size);

void fileWrite(int fd, void *pointer, int size);

int fileDup(int fd);

void fileDup2(int newFd, int oldFd);

void fileUnlink(char *name);

#endif