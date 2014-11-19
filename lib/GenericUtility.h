/*
 * GenericUtility.h
 *
 *  Created on: Nov 8, 2014
 *      Author: ravichandrasadineni
 */

#ifndef GENERICUTILITY_H_
#define GENERICUTILITY_H_
#include <stdio.h>
#include "ODRConstants.h"
#include "unp.h"

typedef struct  {
	char message[FRAME_BUFFER_LENGTH];
	char source[INET_ADDRSTRLEN];
	char destination[INET_ADDRSTRLEN];
	int destinationPort;
	int sourcePort;
	int forceRoute;

}DataPacket;


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




void printFrame (ODRFrame receivedFrame) ;





void getUserChoice(char choice[5]);
void printMacAddress (char haddr[HADDR_LEN]);
void intTochar( int number, char* string);
#endif /* GENERICUTILITY_H_ */

