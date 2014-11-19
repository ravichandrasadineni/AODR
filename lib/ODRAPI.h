/*
 * ODRAPI.h
 *
 *  Created on: Nov 8, 2014
 *      Author: ravichandrasadineni
 */

#ifndef ODRAPI_H_
#define ODRAPI_H_

#include "unp.h"
#include "GenericUtility.h"
#include "ODRConstants.h"

int msg_send(int sockfd, DataPacket packet);
int msg_recv(int sockfd,  DataPacket *packet,struct sockaddr_un* cliaddr);
char* marshallMessage(DataPacket packet);

int  msg_sendTo(int sockfd, DataPacket packet, char fileName[FILE_NAME_LENGTH]);


#endif /* ODRAPI_H_ */
