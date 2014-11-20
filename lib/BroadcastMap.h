/*
 * BroadcastMap.h
 *
 *  Created on: Nov 10, 2014
 *      Author: ravichandrasadineni
 */

#ifndef LIB_BROADCASTMAP_H_
#define LIB_BROADCASTMAP_H_
#include "unp.h"
#include "ODRConstants.h"
#include "MemoryAllocator.h"
#include "AddressUtility.h"

struct brocastList{
	char sourceAddr[INET_ADDRSTRLEN];
	int  brodcastId;
	struct brocastList* next;
};
typedef struct brocastList bList;

int isObselete( char [INET_ADDRSTRLEN],int brodcastId);
int addToBroadCastList( char[INET_ADDRSTRLEN],int brodcastId);

#endif /* LIB_BROADCASTMAP_H_ */
