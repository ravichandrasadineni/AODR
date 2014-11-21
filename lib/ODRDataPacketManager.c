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

int isintendedDestination(char destIPAddr[INET_ADDRSTRLEN]){
	char localAddress[INET_ADDRSTRLEN];
	populateLocalAddress(localAddress);
	if(!strncmp(localAddress, destIPAddr, INET_ADDRSTRLEN)){
		return 1;
	}
	return 0;
}

int canForwardMessage(char destIPAddr[INET_ADDRSTRLEN]){
	if(doesRouteExist(destIPAddr)){
		return 1;
	}
	return 0;
}

void handleDataPacket(ODRFrame currentFrame, int listenedSocket, int *ifSockets, int numOFInf, int udsSocket){
	printf("ODRDataPacketManager.c : Received Data Packet \n");
	if(isintendedDestination(currentFrame.data.destination)){
		char fileName[FILE_NAME_LENGTH];
		//gets filename from portMapper
		getFileName(currentFrame.data.destinationPort, fileName);
		printf("ODRDataPacketManager.c : file name is %s \n ", fileName);
		msg_sendTo(udsSocket, currentFrame.data, fileName);
	}
	else if(canForwardMessage(currentFrame.data.destination)){
		char sourceMacAddr[HADDR_LEN], destMacAddr[HADDR_LEN];
		int Socket = getOutInfForDest(currentFrame.data.destination);
		printf("ODRDataPacketManger.c : Outgoing interface is %d \n", Socket);
		printf("ODRDataPacketManger.c : Destination ip is %s \n", currentFrame.data.destination);
		getSourceMacForInterface(Socket, sourceMacAddr);
		memcpy(currentFrame.header.sourceAddress, sourceMacAddr, HADDR_LEN);
		populateDestMacAddressForRoute(currentFrame.data.destination,destMacAddr);
		memcpy(currentFrame.header.destAddress, destMacAddr, HADDR_LEN);
		char *currentPayload = buildMessageFrame(currentFrame);
		send_rawpacket(Socket, currentPayload);
	}
	else {
		//Parking data..send RREQ
		parkIntoBuffer(currentFrame.data);
		char sourceMacAddr[HADDR_LEN], localAddress[INET_ADDRSTRLEN];
		//Assigning values to header of new RREQ
		getSourceMacForInterface(listenedSocket, sourceMacAddr);
		memcpy(currentFrame.header.sourceAddress, sourceMacAddr, HADDR_LEN);
		memcpy(currentFrame.header.destAddress, BRODCAST_MAC, HADDR_LEN);
		currentFrame.header.hopcount = 0;
		currentFrame.header.Broadcastid = 0;
		currentFrame.header.RREPSent = 0;
		currentFrame.header.packetType = ETH_TYPE;
		//Changing the source address of data packet to currentIp address
		populateLocalAddress(localAddress);
		memcpy(currentFrame.data.source, localAddress, INET_ADDRSTRLEN);
		sendRREQonOtherInterfaces(currentFrame, listenedSocket, ifSockets, numOFInf);
	}
}

void sendDataFrame(DataPacket packet ) {
	ODRFrame currentFrame;
	currentFrame.data= packet;
	int outgoingSocket = getOutInfForDest(packet.destination);
	populateDestMacAddressForRoute(packet.destination, currentFrame.header.destAddress);
	getSourceMacForInterface( outgoingSocket,  currentFrame.header.sourceAddress);
	currentFrame.header.hopcount=0;
	char* frame = buildMessageFrame(currentFrame);
	printf("ODRPacketManager.c :Sending data Packet:");
	send_rawpacket(outgoingSocket,frame);
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
			printf("ODRDataPacketManager.c : Route does not exist \n");

			ODRFrame currentFrame;
			currentFrame.data= packet;
			//Switching off force route in the packet before storing into Parked Buffer
			packet.forceRoute = OFF;
			parkIntoBuffer(packet);
			memcpy(currentFrame.header.destAddress,BRODCAST_MAC, HADDR_LEN);
			currentFrame.header.hopcount=0;
			currentFrame.header.Broadcastid = CURRENT_BRODCAST_ID;
			currentFrame.header.RREPSent = OFF;
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
	printf("Size of ParkedBuffer is %d \n",currentParkingBufferSize);
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





