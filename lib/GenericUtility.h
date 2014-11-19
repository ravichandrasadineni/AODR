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







void getUserChoice(char choice[5]);

void intTochar( int number, char* string);
#endif /* GENERICUTILITY_H_ */

