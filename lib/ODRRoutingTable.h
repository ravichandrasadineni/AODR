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
	char destinationMACAddress[HADDR_LEN];
	char destinationIPAddress[INET_ADDRSTRLEN];
	int socketId;
	int hopcount;
	time_t timeCreated;
	struct ODRrouteEntry *next;
};

typedef struct ODRrouteEntry routeEntry;

void setExpiryTimeForRoutingTable(int secs);
void addRoute(char destinationAddress[HADDR_LEN],char destinationIPAddress[INET_ADDRSTRLEN], int socketId,int hopcount);
void populateDestMacAddressForRoute(char destinationAddress[INET_ADDRSTRLEN], char destMacAddress [HADDR_LEN]);
int getHopCountIfRouteExist(char destinationAddress[INET_ADDRSTRLEN]);
int getOutInfForDest(char destinationAddress[INET_ADDRSTRLEN]);
int getHopCountForROute(char destinationAddress[INET_ADDRSTRLEN]);
void deleteTimeoutEnries();
int doesRouteExist(char destinationAddress[INET_ADDRSTRLEN]);

#endif /* LIB_ODRROUTINGTABLE_H_ */
