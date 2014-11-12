/*
 * ODRRoutingTable.c
 *
 *  Created on: Nov 10, 2014
 *      Author: ravichandrasadineni
 */

int timeout_secs = 0;
#include "ODRRoutingTable.h"

routeEntry *routeTableHead =NULL, *routeTableTail =NULL;

void setExpiryTime(int secs) {
	timeout_secs = secs;
}
void addRoute(char destinationAddress[HADDR_LEN], int socketId,int hopcount) {
	if(routeTableHead == NULL) {
		routeTableHead= (routeEntry*)llocate_void(sizeof(routeEntry));
		routeTableTail = routeTableHead;
	}
	else {
		int currentHopCount = getHopCountIfRouteExist(destinationAddress);
		if((currentHopCount > 0)&&(currentHopCount <hopcount)) {
			return;
		}
		routeTableTail->next = (routeEntry*)allocate_void(sizeof(routeEntry));
		routeTableTail = routeTableTail->next;
	}
	routeTableTail->next = NULL;
	routeTableTail->socketId = socketId;
	routeTableTail->hopcount = hopcount;
	routeTableTail->timeCreated = time_t(NULL);
	strncpy(routeTableTail->destinationAddress,destinationAddress,HADDR_LEN);
}

void deleteEntry(routeEntry* currentPosition, routeEntry* prevPosition ) {
	if(routeTableHead == NULL) {
		return ;
	}
	else if(currentPosition == routeTableHead)
	{
		if(currentPosition == routeTableTail) {
			free(routeTableHead);
			routeTableHead = NULL;
			routeTableTail = NULL;
			return;
		}
		else {
			routeTableHead = routeTableHead->next;
			free(currentPosition);
			return;
		}
	}
	else if(currentPosition == routeTableTail) {
		routeTableTail = prevPosition;
		free(currentPosition);
		routeTableTail ->next = NULL;
	}
	else {
		prevPosition->next = currentPosition->next;
		free(currentPosition);
	}
}

int isTimeExpired(time_t currentTime) {
	int timeDiff = difftime(time(NULL), currentTime);
	if(timeDiff>=timeout_secs) {
		return 1;
	}
	return 0;
}

void deleteTimeoutEnries() {
	routeEntry* currentPosition = routeTableHead;
	routeEntry* prevPosition = NULL;
	while(currentPosition!=NULL) {
		if(isTimeExpired(currentPosition->timeCreated)) {
			routeEntry* positionTODelete = currentPosition;
			currentPosition = currentPosition->next;
			deleteEntry(prevPosition,positionTODelete);
		}
		else {
			prevPosition = currentPosition;
			currentPosition =currentPosition->next;
		}
	}
}

int doesRouteExist(char destinationAddress[HADDR_LEN]) {
	routeEntry* currentPosition = routeTableHead;
	if(routeTableHead == NULL) {
		return 0;
	}
	else  {
		while(currentPosition != NULL) {
			if(strncmp(currentPosition->destinationAddress,destinationAddress,6)) {

				return 1;

			}
			currentPosition = currentPosition->next;
		}
	}

	return 0;
}

int getOutInfForDest(char destinationAddress[HADDR_LEN]) {
	routeEntry* currentPosition = routeTableHead;
	if(routeTableHead == NULL) {
		return 0;
	}
	else  {
		while(currentPosition != NULL) {
			if(strncmp(currentPosition->destinationAddress,destinationAddress,6)) {
				return currentPosition->socketId;

			}
			currentPosition = currentPosition->next;
		}
	}

	return 0;
}

int getHopCountIfRouteExist(char destinationAddress[HADDR_LEN]) {
	routeEntry* currentPosition = routeTableHead;
	if(routeTableHead == NULL) {
		return 0;
	}
	else  {
		while(currentPosition != NULL) {
			if(strncmp(currentPosition->destinationAddress,destinationAddress,6)) {
				return currentPosition->hopcount;

			}
			currentPosition = currentPosition->next;
		}
	}

	return 0;
}
