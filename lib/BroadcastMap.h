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

struct brocastList{
	char brodcastAddr[HADDR_LEN];
	int  brodcastId;
	struct brocastList* next;
};
typedef struct brocastList bList;

int isObselete( char [HADDR_LEN],int brodcastId);
int addToBroadCastList( char[HADDR_LEN],int brodcastId);

#endif /* LIB_BROADCASTMAP_H_ */
