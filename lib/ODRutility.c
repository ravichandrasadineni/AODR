/*
 * ODRutility.c
 *
 *  Created on: Nov 11, 2014
 *      Author: ravichandrasadineni
 */

#include "ODRUtility.h"


void getListeningSet(fd_set *readSet,int *maxfd, int* ifSockets, int count, int UDSsocket) {
	(*maxfd) = 0;
	FD_ZERO(readSet);
	int i;
	for(i=0; i<count; i++) {
		*maxfd = MAX(*maxfd,ifSockets[i]);
		FD_SET(ifSockets[i], readSet);
	}

	FD_SET(UDSsocket, readSet);
	*maxfd = MAX(*maxfd,UDSsocket);
	return;
}




int getTimeOut(int argc, char*argv[]) {

	if (argc != 2) {
		printf("Wrong Input. USage ODR <timeoutSecs> \n");
		exit(2);
	}
	return atoi(argv[1]);
}
