/*
 * RREPManager.c
 *
 *  Created on: Nov 19, 2014
 *      Author: harsha
 */
#include "ODRRREPManager.h"

int shouldSendRREQ(ODRFrame currentFrame){
	//If route doesn't exist Send RREQ
	if(!doesRouteExist(currentFrame.data.destination)){
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
void handleRREP(ODRFrame currentFrame, int listenedSocket, int *ifSockets, int numofInter){
	printf("Recieved RREP \n");
	if(isDestination(currentFrame)){
		printf("Sending packet in Parked Buffer :\n");
		addRoute(currentFrame.header.sourceAddress,currentFrame.data.source,listenedSocket,currentFrame.header.hopcount-1,currentFrame.data.forceRoute);
		sendPacketWaitingInBuffer();
	}
	else if(canForwardRREP(currentFrame)){
		printf("Forwarding RREP:\n");
		char destMacAddr[HADDR_LEN], sourceMacAddr[HADDR_LEN];
		populateDestMacAddressForRoute(currentFrame.data.destination,destMacAddr);
		memcpy(currentFrame.header.destAddress,  destMacAddr, HADDR_LEN);
		getSourceMacForInterface(listenedSocket,sourceMacAddr);
		memcpy(currentFrame.header.sourceAddress, sourceMacAddr, HADDR_LEN);
		char* MarshalledFrame = buildRREP(currentFrame);
		int Socket = getOutInfForDest(currentFrame.data.destination);
		send_rawpacket(Socket,MarshalledFrame);
		free(MarshalledFrame);
	}
	else if(shouldSendRREQ(currentFrame)){
		char sourceMacAddr[HADDR_LEN], sourceIPAddr[INET_ADDRSTRLEN];
		//Parking RREP into buffer
		parkIntoBuffer(currentFrame.data);
		//Rebuilding RREQ from the currentFrame
		getSourceMacForInterface(listenedSocket,sourceMacAddr);
		memcpy(currentFrame.header.sourceAddress, sourceMacAddr, HADDR_LEN);
		memcpy(currentFrame.header.destAddress, BRODCAST_MAC, HADDR_LEN);
		currentFrame.header.RREPSent = 0;
		currentFrame.header.hopcount = 0;
		currentFrame.header.Broadcastid = 0;
		populateLocalAddress(sourceIPAddr);
		memcpy(currentFrame.data.source, sourceIPAddr, INET_ADDRSTRLEN);
		sendRREQonOtherInterfaces(currentFrame, listenedSocket, ifSockets, numofInter);
	}
}


