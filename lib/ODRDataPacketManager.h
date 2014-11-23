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
#include "AddressUtility.h"

void intializeBufferTimeOut(int timeOut);
void parkIntoBuffer(ODRFrame frame);
void sendDataPacket(DataPacket packet,int udsSocket,int *ifSockets,int numOFInf);
int isPacketWaitingForDestination(char destiNationAddress[INET_ADDRSTRLEN]);
void RetrievePacketsForDestination(char destiNationAddress[INET_ADDRSTRLEN], DataPacket *destinationPackets);
void handleDataPacket(ODRFrame currentFrame, int listenedSocket, int *ifSockets, int numOFInf, int udsSocket);
void sendPacketWaitingInBuffer(int outGoingSocket, char destMacAddr[HADDR_LEN], char destIPAddress[INET_ADDRSTRLEN]);


#endif /* LIB_ODRDATAPACKETMANAGER_H_ */
