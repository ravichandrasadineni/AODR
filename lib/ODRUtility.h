/*
 * ODRUtility.h
 *
 *  Created on: Nov 11, 2014
 *      Author: ravichandrasadineni
 */

#ifndef LIB_ODRUTILITY_H_
#define LIB_ODRUTILITY_H_

#include "unp.h"
#include "ODRConstants.h"
#include "GenericUtility.h"
#include "FrameSendRecvUtility.h"
#include "FrameBufferUtility.h"
void getListeningSet(fd_set *readSet,int *maxfd, int* ifSockets, int count, int UDSsocket);
void sendRREQonOtherInterfaces(ODRFrame currentFrame, int listenedSocket,int *ifSockets,int numOFInf );
void sendRREQonAllInterfaces(ODRFrame currentFrame, int *ifSockets,int numOfInf);
int getTimeOut(int argc, char*argv[]) ;
DataPacket getData(int sockfd,struct sockaddr_un* cliaddr);

#endif /* LIB_ODRUTILITY_H_ */
