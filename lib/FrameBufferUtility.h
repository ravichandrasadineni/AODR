/*
 * FrameBufferUtility.h
 *
 *  Created on: Nov 9, 2014
 *      Author: ravichandrasadineni
 */

#ifndef LIB_FRAMEBUFFERUTILITY_H_
#define LIB_FRAMEBUFFERUTILITY_H_
#include "MemoryAllocator.h"
#include "ODRConstants.h"
#include <string.h>
#include<stdlib.h>
#include<stdio.h>

void breakBuffer(char* sourceMac, char* destinationMac, char *data, void* buffer);
void buildBuffer(char* sourceMac, char* destinationMac, char *data, void* buffer);
typedef struct {
	int packetType;
	int Broadcastid;
	char sourceAddress[HADDR_LEN];
	char destAddress[HADDR_LEN];
	int hopcount;
}ODRHeader;

typedef struct{
	ODRHeader header;
	char *payload;
}ODRPacket;
#endif /* LIB_FRAMEBUFFERUTILITY_H_ */
