/*
 * FrameBufferUtility.h
 *
 *  Created on: Nov 9, 2014
 *      Author: ravichandrasadineni
 */
#include "ODRAPI.h"
#ifndef LIB_FRAMEBUFFERUTILITY_H_
#define LIB_FRAMEBUFFERUTILITY_H_
#include "MemoryAllocator.h"
#include "ODRConstants.h"
#include <string.h>
#include<stdlib.h>
#include <linux/if_ether.h>
#include<stdio.h>



typedef struct {
	int packetType;
	int Broadcastid;
	char sourceAddress[HADDR_LEN];
	char destAddress[HADDR_LEN];
	int hopcount;
}ODRHeader;

typedef struct{
	ODRHeader header;
	DataPacket data;
}ODRFrame;
char* buildRREQ(ODRFrame currentFrame);
char* buildRREP(ODRFrame currentFrame);
char* buildMessageFrame(ODRFrame currentFrame);


#endif /* LIB_FRAMEBUFFERUTILITY_H_ */
