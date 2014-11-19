/*
 * FrameBufferUtility.c
 *
 *  Created on: Nov 9, 2014
 *      Author: ravichandrasadineni
 */
#include "FrameBufferUtility.h"

void buildFrame(char* sourceMac, char* destinationMac, char *data, char* frame) {
	if(data == NULL) {
		printf("FrameBufferUtility.c: data is NULL \n");
		exit(0);
	}
	if(frame == NULL) {
		printf("FrameBufferUtility.c: frame is NULL \n");
		exit(0);
	}
	unsigned short type=htons(ETH_TYPE);
	memcpy(frame,destinationMac,HADDR_LEN);
	memcpy(frame+HADDR_LEN,sourceMac,HADDR_LEN);
	memcpy(frame+2*HADDR_LEN,(unsigned char *)&type,ETH_TYPE_LEN);
	memcpy(frame+2*HADDR_LEN+ETH_TYPE_LEN,data,strlen(data));
	printf("FrameBufferUtility.c : The frame after building is %s \n",frame);
}

char * MarshalledFramePayload(ODRFrame currentFrame) {
	char hopcount[HOPCOUNT_LENGTH +1], brodcastId[BRODCAST_ID_LENGTH+1];
	memset(hopcount,'\0',HOPCOUNT_LENGTH);
	memset(brodcastId,'\0',BRODCAST_ID_LENGTH);
	char * data = marshallMessage(currentFrame.data);
	char* frame = allocate_strmem(FRAME_BUFFER_LENGTH);
	sprintf(hopcount,"%d",currentFrame.header.hopcount);
	sprintf(brodcastId,"%d",currentFrame.header.Broadcastid);
	printf("FrameBufferUtility.c : packettype value is %d\n",currentFrame.header.packetType);
	sprintf(frame,"%d",currentFrame.header.packetType);
	strncat(frame,DELIMETER, strlen(DELIMETER));
	strncat(frame,hopcount,HOPCOUNT_LENGTH);
	strncat(frame,DELIMETER, strlen(DELIMETER));
	strncat(frame,brodcastId,BRODCAST_ID_LENGTH);
	strncat(frame,DELIMETER, strlen(DELIMETER));
	strncat(frame,data,strlen(data));
	printf("FrameBufferUtility.c : Frame is %s \n", frame);
	free(data);
	return frame;
}

void breakFrame(char* sourceMac, char* destinationMac, char *data, void* buffer) {
	int i,dataSize;
	int length = sizeof((char*)buffer);
	dataSize = length - sizeof(sourceMac) - sizeof(destinationMac) - ETH_TYPE_LEN;
	strncat(sourceMac, ((char*)buffer),HADDR_LEN);
	strncat(destinationMac, ((char*)buffer)+HADDR_LEN,HADDR_LEN);
	strncat(data, ((char*)buffer)+2 * HADDR_LEN + 2,dataSize);
}



char* buildRREQ(ODRFrame currentFrame){
	currentFrame.header.packetType = 0;
	char* frame = allocate_strmem(FRAME_LENGTH);
	char* dataPayLoad = MarshalledFramePayload(currentFrame);
	printf("FrameBufferUtility.c : The source address is %s Destination address is %s\n",currentFrame.header.sourceAddress,currentFrame.header.destAddress);
	buildFrame(currentFrame.header.sourceAddress, currentFrame.header.destAddress, dataPayLoad,frame);
	free(dataPayLoad);
	return frame;
}

char* buildRREP(ODRFrame currentFrame){
	currentFrame.header.packetType = 1;
	currentFrame.header.Broadcastid =0;
	char* frame = allocate_strmem(FRAME_LENGTH);
	char* dataPayLoad = MarshalledFramePayload(currentFrame);
	buildFrame(currentFrame.header.sourceAddress, currentFrame.header.destAddress, dataPayLoad,frame);
	free(dataPayLoad);
	return frame;
}

char* buildMessageFrame(ODRFrame currentFrame){
	currentFrame.header.packetType = 2;
	currentFrame.header.Broadcastid =0;
	char* frame = allocate_strmem(FRAME_LENGTH);
	memset(frame,'\0',FRAME_LENGTH);
	char* dataPayLoad = MarshalledFramePayload(currentFrame);
	buildFrame(currentFrame.header.sourceAddress, currentFrame.header.destAddress, dataPayLoad,frame);
	free(dataPayLoad);
	return frame;
}

