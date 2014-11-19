/*
 * ODRMessageBuffer.h
 *
 *  Created on: Nov 12, 2014
 *      Author: ravichandrasadineni
 */

#ifndef LIB_ODRDATAPACKETMANAGER_H_
#define LIB_ODRDATAPACKETMANAGER_H_

#include "unp.h"
#include "ODRConstants.h"
#include "ODRUtility.h"
#include "ODRAPI.h"
#include "ODRsocketUtility.h"
#include "FilePortMapper.h"
#include "FrameBufferUtility.h"
#include "FrameSendRecvUtility.h"

void intializeBufferTimeOut(int timeOut);
void parkIntoBuffer(DataPacket packet);
void sendDataPacket(DataPacket packet,int udsSocket,int *ifSockets,int numOFInf);
int isPacketWaitingForDestination(char destiNationAddress[INET_ADDRSTRLEN]);
void RetrievePacketsForDestination(char destiNationAddress[INET_ADDRSTRLEN], DataPacket *destinationPackets);

#endif /* LIB_ODRDATAPACKETMANAGER_H_ */