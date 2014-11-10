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

void buildRREQ(char *sourceMac, char* destinationMac, char *data, int broadcastInter, ODRHeader *currentPacket){
	currentPacket->packetType = 0;
	currentPacket->destAddress = destinationMac;
	currentPacket->sourceAddress = sourceMac;
	currentPacket->hopcount = 0;
	currentPacket->Broadcastid = broadcastInter;
}

void buildRREP(char *sourceMac, char* destinationMac, char *data, int broadcastInter, ODRHeader *currentPacket){
	currentPacket->packetType = 1;
	currentPacket->destAddress = destinationMac;
	currentPacket->sourceAddress = sourceMac;
	currentPacket->hopcount = 0;
	currentPacket->Broadcastid = broadcastInter;
}

ODRPacket* buildPayload(char *sourceMac, char* destinationMac, char *data, int broadcastInter, ODRHeader *currentPacket){
	ODRPacket *MsgPacket;
	currentPacket->packetType = 2;
	currentPacket->destAddress = destinationMac;
	currentPacket->sourceAddress = sourceMac;
	currentPacket->hopcount = 0;
	currentPacket->Broadcastid = broadcastInter;
	MsgPacket->header = currentPacket;
	MsgPacket->payload = data;
	return MsgPacket;
}

