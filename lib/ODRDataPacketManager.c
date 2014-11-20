/*
 * ODRMessageBuffer.c
 *
 *  Created on: Nov 12, 2014
 *      Author: ravichandrasadineni
 */
#include "ODRDataPacketManager.h"


int timeOutSecs =0;
int CURRENT_BRODCAST_ID= 0;
DataPacket parkingBuffer[DATAPACKET_BUFFER_SIZE];
int currentParkingBufferSize =0;
void intializeBufferTimeOut(int timeOut) {
	timeOutSecs = timeOut;
}


void sendDataFrame(DataPacket packet ) {
	ODRFrame currentFrame;
	currentFrame.data= packet;
	int outgoingSocket = getOutInfForDest(packet.destination);
	populateDestMacAddressForRoute(packet.destination, currentFrame.header.destAddress);
	getSourceMacForInterface( outgoingSocket,  currentFrame.header.sourceAddress);
	currentFrame.header.hopcount=0;
	char* frame = buildMessageFrame(currentFrame);
	send_rawpacket(outgoingSocket,frame);
	printf("ODRDataPacketManager.c :FRAME SENT IS  %s \n",frame);
	free(frame);
}

void parkIntoBuffer(DataPacket packet) {
	parkingBuffer[currentParkingBufferSize] = packet;
	currentParkingBufferSize ++;
}

void sendDataPacket(DataPacket packet,int udsSocket,int *ifSockets,int numOFInf)  {
	if(!(strncmp(packet.destination,packet.source,INET_ADDRSTRLEN))) {
		printf("ODRDataPacketManager.c  : LocalHost communication \n");
		char destinationPath[FILE_NAME_LENGTH];
		getFileName(packet.destinationPort,destinationPath);
		printf("ODRDataPacketManager.c  : Destination File Path is %s \n",destinationPath);
		msg_sendTo(udsSocket,packet,destinationPath );
	}
	else {
		if((doesRouteExist(packet.destination))&&(!packet.forceRoute)) {
			sendDataFrame(packet);
		}
		else {
			printf("Route does not exist \n");
			parkIntoBuffer(packet);
			ODRFrame currentFrame;
			currentFrame.data= packet;
			memcpy(currentFrame.header.destAddress,BRODCAST_MAC, HADDR_LEN);
			currentFrame.header.hopcount=0;
			currentFrame.header.Broadcastid = CURRENT_BRODCAST_ID;
			currentFrame.header.RREPSent = 0;
			int i;
			sendRREQonAllInterfaces(currentFrame,ifSockets,numOFInf);
		}
	}
}


void removeParkedPacket(int i) {
	int j;
	for(j=i+1; j<currentParkingBufferSize; j++) {
		parkingBuffer[j-1] = parkingBuffer[j];
	}
	currentParkingBufferSize--;
}

void sendPacketWaitingInBuffer()  {
	int i;
	for(i=0; i<currentParkingBufferSize; ){
		DataPacket currentParkedPacket;
		currentParkedPacket = parkingBuffer[i];
		if(doesRouteExist(currentParkedPacket.destination)) {
			sendDataFrame(currentParkedPacket);
			removeParkedPacket(i);
			//we have removed the current packet. so the next packet will be in the current position
		}
		else {
			i++;
		}
	}
}





