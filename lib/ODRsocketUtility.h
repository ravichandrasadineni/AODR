/*
 * ODRsocketUtility.h
 *
 *  Created on: Nov 9, 2014
 *      Author: ravichandrasadineni
 */

#ifndef LIB_ODRSOCKETUTILITY_H_
#define LIB_ODRSOCKETUTILITY_H_
#include "unp.h"
#include "ODRConstants.h"
#include "MemoryAllocator.h"
typedef struct  {
	char    if_haddr[IF_HADDR];	/* hardware address */
	int     if_index;
	ifInfo * next;

}ifInfo;

void createAndBindSocketsTOInterfaces(int* sockets, int number);
void getListOfInterfaces(ifInfo* ifList, int* size );
struct sockaddr_ll getBindedSocket(int sockfd);
int createNewSocket();
#endif /* LIB_ODRSOCKETUTILITY_H_ */
