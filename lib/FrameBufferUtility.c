/*
 * FrameBufferUtility.c
 *
 *  Created on: Nov 9, 2014
 *      Author: ravichandrasadineni
 */
#include "FrameBufferUtility.h"
#include "ODRConstants.h"



void breakBuffer(char* sourceMac, char* destinationMac, char *data, void* buffer) {
	int i,dataSize;
	int length = sizeof((char*)buffer);
	dataSize = length - sizeof(sourceMac) - sizeof(destinationMac) - TYPE_SIZE;
	strncat(sourceMac, ((char*)buffer),HADDR_LEN);
	strncat(destinationMac, ((char*)buffer)+HADDR_LEN,HADDR_LEN);
	strncat(data, ((char*)buffer)+2 * HADDR_LEN + 2,dataSize);
}


void buildBuffer(char* sourceMac, char* destinationMac, char *data, void* buffer) {
	strncat(((char*)buffer), sourceMac, HADDR_LEN);
	strncat(((char*)buffer)+HADDR_LEN, destinationMac, HADDR_LEN);
	strncat(((char*)buffer)+2 * HADDR_LEN, ETH_TYPE,TYPE_SIZE);
	strncat(((char*)buffer)+2 * HADDR_LEN + 2, data, sizeof(data));
}

void buildRREQ(char *sourceMac, char* destinationMac, char *data, ODRHeader *currentPacket){
	currentPacket->packetType = 0;
	strcpy(currentPacket->destAddress, destinationMac);
	strcpy(currentPacket->sourceAddress, sourceMac);
	currentPacket->hopcount = 0;
}

void buildRREP(char *sourceMac, char* destinationMac, char *data, ODRHeader *currentPacket){
	currentPacket->packetType = 1;
	strcpy(currentPacket->destAddress, destinationMac);
	strcpy(currentPacket->sourceAddress, sourceMac);
	currentPacket->hopcount = 0;
}

ODRPacket* buildPayload(char *sourceMac, char* destinationMac, char *data, ODRHeader *currentPacket){
	ODRPacket *MsgPacket;
	currentPacket->packetType = 2;
	strcpy(currentPacket->destAddress, destinationMac);
	strcpy(currentPacket->sourceAddress, sourceMac);
	currentPacket->hopcount = 0;
	MsgPacket->header = currentPacket;
	strcpy(MsgPacket->payload, data);
	return MsgPacket;
}

