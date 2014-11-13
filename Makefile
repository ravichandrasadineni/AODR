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
all: client  server ODR

OBJECTS=AddressUtility.o GenericUtility.o ODRAPI.o UDSUtility.o MemoryAllocator.o ODRsocketUtility.o FilePortMapper.o get_hw_addrs.o BroadcastMap.o ODRutility.o ODRRoutingTable.o


client: client.o $(OBJECTS)
	${CC} ${FLAGS} -o client client.o $(OBJECTS) ${LIBS}
	
server: server.o $(OBJECTS)
	${CC} ${FLAGS} -o server server.o $(OBJECTS) ${LIBS}


ODR: ODR.o $(OBJECTS)
	${CC} ${FLAGS} -o ODR ODR.o $(OBJECTS) ${LIBS}

ODR.o: ODR.c
	${CC} ${CFLAGS} -c ODR.c
	
client.o: client.c 
	${CC} ${CFLAGS} -c client.c
	
server.o: server.c 
	${CC} ${CFLAGS} -c server.c 

AddressUtility.o: lib/AddressUtility.c
	${CC} ${CFLAGS} -c lib/AddressUtility.c

GenericUtility.o: lib/GenericUtility.c
	${CC} ${CFLAGS} -c lib/GenericUtility.c
	
ODRAPI.o: lib/ODRAPI.c
	${CC} ${CFLAGS} -c lib/ODRAPI.c
	
UDSUtility.o: lib/UDSUtility.c
	${CC} ${CFLAGS} -c lib/UDSUtility.c
	
ODRutility.o: lib/ODRutility.c
	${CC} ${CFLAGS} -c lib/ODRutility.c
	
MemoryAllocator.o: lib/MemoryAllocator.c
	${CC} ${CFLAGS} -c lib/MemoryAllocator.c
	
ODRsocketUtility.o: lib/ODRsocketUtility.c
	${CC} ${CFLAGS} -c lib/ODRsocketUtility.c

FilePortMapper.o: lib/FilePortMapper.c
	${CC} ${CFLAGS} -c lib/FilePortMapper.c
	
BroadcastMap.o: lib/BroadcastMap.c
	${CC} ${CFLAGS} -c lib/BroadcastMap.c
	
ODRRoutingTable.o: lib/ODRRoutingTable.c
	${CC} ${CFLAGS} -c lib/ODRRoutingTable.c
	
get_hw_addrs.o: lib/Asgn3_code/get_hw_addrs.c
	${CC} ${CFLAGS} -c lib/Asgn3_code/get_hw_addrs.c



clean:
	rm  client server $(OBJECTS)

