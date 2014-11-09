
CC = gcc

LIBS =  /home/courses/cse533/Stevens/unpv13e/libunp.a

FLAGS = -g -O2

all: get_hw_addrs.o prhwaddrs.o
	${CC} -o prhwaddrs prhwaddrs.o get_hw_addrs.o ${LIBS}
get_hw_addrs.o: get_hw_addrs.c
	${CC} ${FLAGS} -c get_hw_addrs.c

prhwaddrs.o: prhwaddrs.c
	${CC} ${FLAGS} -c prhwaddrs.c

clean:
	rm prhwaddrs prhwaddrs.o get_hw_addrs.o

