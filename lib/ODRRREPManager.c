/*
 * RREPManager.c
 *
 *  Created on: Nov 19, 2014
 *      Author: harsha
 */
#include "ODRRREPManager.h"

int shouldSendRREQ(ODRFrame currentFrame){
	char localAddress[INET_ADDRSTRLEN];
	populateLocalAddress(localAddress);
	//If route doesn't exist Send RREQ
	if(!doesRouteExist(localAddress)){
		return 1;
	}

	return 0;
}

int canForwardRREP(ODRFrame currentFrame){
	//If route available Forward the RREP
	if(doesRouteExist(currentFrame.data.destination)){
		return 1;
	}
	return 0;
}
int isDestination(ODRFrame currentFrame){
	char localAddress[INET_ADDRSTRLEN];
	populateLocalAddress(localAddress);
	if(!strncmp(currentFrame.data.destination,localAddress, INET_ADDRSTRLEN)){
		return 1;
	}
	return 0;
}


void handleRREP(ODRFrame currentFrame){
	if(isDestination(currentFrame)){
		printf("Sending packet in Parked Buffer :");
		sendPacketWaitingInBuffer();
	}
	else if(canForwardRREP(currentFrame)){
		ODRFrame *frametoSend = &currentFrame;
		int outSocket = getOutInfForDest(currentFrame.data.destination);
		send_rawpacket(outSocket,(char *)frametoSend);

	}
	else if(shouldSendRREQ(currentFrame)){
		//Parking data into buffer
		parkIntoBuffer(currentFrame.data);

	}
}


