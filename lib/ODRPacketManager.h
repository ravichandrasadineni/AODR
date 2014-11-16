/*
 * ODRMessageBuffer.h
 *
 *  Created on: Nov 12, 2014
 *      Author: ravichandrasadineni
 */

#ifndef LIB_ODRMESSAGEBUFFER_H_
#define LIB_ODRMESSAGEBUFFER_H_

#include "unp.h"
#include "ODRConstants.h"
#include "ODRUtility.h"

void intializeBufferTimeOut(int timeOut);
void parkIntoBuffer(DataPacket packet);
void sendPacket(DataPacket packet);
int isPacketWaitingForDestination(char destiNationAddress[INET_ADDRSTRLEN]);
RetrievePacketsForDestination(char destiNationAddress[INET_ADDRSTRLEN], DataPacket *destinationPackets);

#endif /* LIB_ODRMESSAGEBUFFER_H_ */
