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
	*maxfd = *maxfd+1;
	return;
}

void sendRREQonOtherInterfaces(ODRFrame currentFrame, int listenedSocket,int *ifSockets,int numOFInf ) {
	int i;
	for (i=0; i <numOFInf; i++) {
		if(ifSockets[i]!= listenedSocket) {
			getSourceMacForInterface( ifSockets[i],  currentFrame.header.sourceAddress);
			memcpy(currentFrame.header.destAddress,BRODCAST_MAC, HADDR_LEN);
			printf("ODRDataPacketManager.c  : Source Mac Address is : ");
			printMacAddress(currentFrame.header.sourceAddress);
			printf("ODRDataPacketManager.c  : Destination Mac Address is :");
			printMacAddress(currentFrame.header.destAddress);
			char* frame = buildRREQ(currentFrame);
			send_rawpacket(ifSockets[i], frame);
			printf("ODRDataPacketManager.c  :FRAME SENT IS  %s \n",frame);
			free(frame);
		}
	}

}
void sendRREQonAllInterfaces(ODRFrame currentFrame, int *ifSockets,int numOfInf) {
	sendRREQonOtherInterfaces(currentFrame,-1,ifSockets, numOfInf);
}

DataPacket getData(int sockfd,struct sockaddr_un* cliaddr)  {
	DataPacket newDataPacket;
	msg_recv(sockfd,  &newDataPacket, cliaddr);
	return newDataPacket;

}



int getTimeOut(int argc, char*argv[]) {

	if (argc != 2) {
		printf("Wrong Input. USage ODR <timeoutSecs> \n");
		exit(2);
	}
	return atoi(argv[1]);
}
