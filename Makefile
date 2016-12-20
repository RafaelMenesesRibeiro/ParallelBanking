CFLAGS = -g -Wall -pedantic -pthread

#Compiles all files
all: i-banco-terminal i-banco

#Compiles just the i-banco-terminal
i-banco-terminal: filemanager.o structure.o comreader.o errorhandling.o i-banco-terminal.o
	gcc $(CFLAGS) -o i-banco-terminal filemanager.o structure.o comreader.o errorhandling.o i-banco-terminal.o

errorhandling.o: errorhandling.h errorhandling.c
	gcc $(CFLAGS) -c errorhandling.c

comreader.o: comreader.h comreader.c
	gcc $(CFLAGS) -c comreader.c

i-banco-terminal.o: filemanager.h structure.h comreader.h errorhandling.h i-banco-terminal.h i-banco-terminal.c
	gcc $(CFLAGS) -c i-banco-terminal.c 

#Compile just the i-banco
i-banco: filemanager.o synchronization.o structure.o errorhandling.o accounts.o thread.o i-banco.o
	gcc $(CFLAGS) -o i-banco filemanager.o synchronization.o structure.o errorhandling.o accounts.o thread.o i-banco.o

thread.o: synchronization.h structure.h errorhandling.h accounts.h thread.h thread.c
	gcc $(CFLAGS) -c thread.c

accounts.o: synchronization.h accounts.h accounts.c
	gcc $(CFLAGS) -c accounts.c

structure.o: structure.h structure.c
	gcc $(CFLAGS) -c structure.c

synchronization.o: synchronization.h synchronization.c
	gcc $(CFLAGS) -c synchronization.c

filemanager.o: filemanager.h filemanager.c
	gcc $(CFLAGS) -c filemanager.c	

i-banco.o: filemanager.h synchronization.h errorhandling.h thread.h accounts.h i-banco.h i-banco.c
	gcc $(CFLAGS) -c i-banco.c

run:
	./i-banco

clean:
	rm *.o *.txt i-banco i-banco-terminal i-banco-pipe*

zip:
	zip SO_Projeto_EX4_Grupo55_22 *.c *.h Makefile