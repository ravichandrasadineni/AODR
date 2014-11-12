/*
 * ODRRoutingTableUtility.h
 *
 *  Created on: Nov 10, 2014
 *      Author: ravichandrasadineni
 */

#ifndef LIB_ODRROUTINGTABLE_H_
#define LIB_ODRROUTINGTABLE_H_
#include "unp.h"
#include "MemoryAllocator.h"
#include "ODRConstants.h"

struct ODRrouteEntry {
	char destinationAddress[HADDR_LEN];
	int socketId;
	int hopcount;
	time_t timeCreated;
	struct ODRrouteEntry *next;
};

typedef struct ODRrouteEntry routeEntry;

void setExpiryTime(int secs);
void addRoute(char destinationAddress[HADDR_LEN], int interfaceId,int hopcount);
int getHopCountIfRouteExist(char destinationAddress[HADDR_LEN]);
int getOutInfForDest(char destinationAddress[HADDR_LEN]);
void deleteTimeoutEnries();
void doesRouteExist(char destinationAddress[HADDR_LEN]);



#endif /* LIB_ODRROUTINGTABLE_H_ */
