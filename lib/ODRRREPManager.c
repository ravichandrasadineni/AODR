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

//handleRREP(currentFrame,setSocket,*ifSockets,numOFInf);
void handleRREP(ODRFrame currentFrame, int setSocket, int *ifSockets, int numofInter){
	if(isDestination(currentFrame)){
		printf("Sending packet in Parked Buffer :");
		sendPacketWaitingInBuffer();
	}
	else if(canForwardRREP(currentFrame)){
		char destMacAddr[HADDR_LEN], sourceMacAddr[HADDR_LEN];
		populateDestMacAddressForRoute(currentFrame.data.destination,destMacAddr);
		memcpy(currentFrame.header.destAddress,  destMacAddr, HADDR_LEN);
		getSourceMacForInterface(setSocket,sourceMacAddr);
		memcpy(currentFrame.header.sourceAddress, sourceMacAddr, HADDR_LEN);
		send_rawpacket(setSocket,(char *)&currentFrame);
	}
	else if(shouldSendRREQ(currentFrame)){
		char sourceMacAddr[HADDR_LEN];
		//Parking data into buffer
		parkIntoBuffer(currentFrame.data);
		getSourceMacForInterface(setSocket,sourceMacAddr);
		memcpy(currentFrame.header.sourceAddress, sourceMacAddr, HADDR_LEN);
		memcpy(c)
		sendRREQonOtherInterfaces(currentFrame, setSocket, ifSockets, numofInter);

	}
}


