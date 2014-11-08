
# This is a sample Makefile which compiles source files named:
# - tcpechotimeserv.c
# - tcpechotimecli.c
# - time_cli.c
# - echo_cli.c
# and creating executables: "server", "client", "time_cli"
# and "echo_cli", respectively.
#
# It uses various standard libraries, and the copy of Stevens'
# library "libunp.a" in ~cse533/Stevens/unpv13e_solaris2.10 .
#
# It also picks up the thread-safe version of "readline.c"
# from Stevens' directory "threads" and uses it when building
# the executable "server".
#
# It is set up, for illustrative purposes, to enable you to use
# the Stevens code in the ~cse533/Stevens/unpv13e_solaris2.10/lib
# subdirectory (where, for example, the file "unp.h" is located)
# without your needing to maintain your own, local copies of that
# code, and without your needing to include such code in the
# submissions of your assignments.
#
# Modify it as needed, and include it with your submission.

CC = gcc

LIBS = -lresolv -lnsl -pthread -lm unpv13e/libunp.a 
	
FLAGS = -g -O0

CFLAGS = ${FLAGS} -I unpv13e/lib
all: client  

OBJECTS=AddressUtility.o GenericUtility.o


client: client.o $(OBJECTS)
	${CC} ${FLAGS} -o client client.o $(OBJECTS) ${LIBS}
	
AddressUtility.o: lib/AddressUtility.c
	${CC} ${CFLAGS} -c lib/AddressUtility.c

GenericUtility.o: lib/GenericUtility.c
	${CC} ${CFLAGS} -c lib/GenericUtility.c



clean:
	rm  client  $(OBJECTS)

