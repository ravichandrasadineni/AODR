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
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>
#include "Asgn3_code/hw_addrs.h"

struct interfacefInfo {
	char    if_haddr[IF_HADDR];	/* hardware address */
	int     if_index;
	struct interfacefInfo  *next;

}interfacefInfo ;

typedef struct interfacefInfo  ifInfo;

void createAndBindSocketsTOInterfaces(int* sockets, int* number);
void getListOfInterfaces(ifInfo* ifList, int* size );
struct sockaddr_ll getODRBindedSocket(int sockfd);
int createNewSocket();
#endif /* LIB_ODRSOCKETUTILITY_H_ */
