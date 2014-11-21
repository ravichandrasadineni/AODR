/*
 * ODRRoutingTable.c
 *
 *  Created on: Nov 10, 2014
 *      Author: ravichandrasadineni
 */


#include "ODRRoutingTable.h"
int timeout_secs = 0;
routeEntry *routeTableHead =NULL, *routeTableTail =NULL;

void deleteRouteEntry(routeEntry* currentPosition, routeEntry* prevPosition );
void setExpiryTimeForRoutingTable(int secs) {
	timeout_secs = secs;
}


void printRoutingTable() {
	routeEntry* currentPosition = routeTableHead;
	if(routeTableHead == NULL) {
		printf("No entries \n");
	}
	else  {
		while(currentPosition != NULL) {
			printf("%s \t",currentPosition->destinationIPAddress);
			printf("%d \t",currentPosition->hopcount);
			printf("%d \t",currentPosition->socketId);
			printf("%.24s \t",ctime(&currentPosition->timeCreated));
			printMacAddress(currentPosition->destinationMACAddress);
			currentPosition = currentPosition->next;
		}
	}

}




void addRoute(char destinationMACAddress[HADDR_LEN],char destinationIPAddress[INET_ADDRSTRLEN],  int socketId,int hopcount, int forceroute) {
	deleteTimeoutEnries();
	printf("Before adding Route \n");
	printRoutingTable();
	if(routeTableHead == NULL) {
		routeTableHead= (routeEntry*)allocate_void(sizeof(routeEntry));
		routeTableTail = routeTableHead;
	}
	else {
		if(forceroute == 1){
			deleteRoute(destinationIPAddress);
		}
		else{
			int currentHopCount = getHopCountIfRouteExist(destinationIPAddress);
			if((currentHopCount > 0)&&(currentHopCount <hopcount)) {
				return;
			}
			deleteRoute(destinationIPAddress);
		}
		if(routeTableTail == NULL) {
			routeTableHead= (routeEntry*)allocate_void(sizeof(routeEntry));
			routeTableTail = routeTableHead;
		}
		else {
			routeTableTail->next = (routeEntry*)allocate_void(sizeof(routeEntry));
			routeTableTail = routeTableTail->next;
		}

	}
	routeTableTail->next = NULL;
	routeTableTail->socketId = socketId;
	routeTableTail->hopcount = hopcount;
	strncpy(routeTableTail->destinationIPAddress,destinationIPAddress,INET_ADDRSTRLEN);
	routeTableTail->timeCreated = time(NULL);
	memcpy(routeTableTail->destinationMACAddress,destinationMACAddress,HADDR_LEN);
	printf("After adding Route \n");
	printRoutingTable();

}


void deleteRoute(char destinationIPAddress[INET_ADDRSTRLEN]) {
	routeEntry* currentPosition = routeTableHead;
	routeEntry* prevPosition  = NULL;
	if(routeTableHead == NULL) {
		return ;
	}
	else {
		while(currentPosition != NULL) {

			if(!strncmp(currentPosition->destinationIPAddress,destinationIPAddress,INET_ADDRSTRLEN)) {
				deleteRouteEntry(currentPosition,prevPosition);
				return;
			}
			prevPosition = currentPosition;
			currentPosition = currentPosition->next;
		}
	}

}


void deleteRouteEntry(routeEntry* currentPosition, routeEntry* prevPosition ) {
	printf("ODRROUTINGTABLE.C : Before deleting Route \n");
	printRoutingTable();
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
	printf("ODRROUTINGTABLE.C :After deleting Route \n");
	printRoutingTable();
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
			deleteRouteEntry(positionTODelete,prevPosition);
		}
		else {
			prevPosition = currentPosition;
			currentPosition =currentPosition->next;
		}
	}
}

int doesRouteExist(char destinationAddress[INET_ADDRSTRLEN]) {
	deleteTimeoutEnries();
	routeEntry* currentPosition = routeTableHead;
	if(routeTableHead == NULL) {
		return 0;
	}
	else  {
		while(currentPosition != NULL) {
			if(!strncmp(currentPosition->destinationIPAddress,destinationAddress,INET_ADDRSTRLEN)) {

				return 1;

			}
			currentPosition = currentPosition->next;
		}
	}

	return 0;
}

int getOutInfForDest(char destinationAddress[INET_ADDRSTRLEN]) {
	deleteTimeoutEnries();
	routeEntry* currentPosition = routeTableHead;
	if(routeTableHead == NULL) {
		return 0;
	}
	else  {
		while(currentPosition != NULL) {
			if(!strncmp(currentPosition->destinationIPAddress,destinationAddress,INET_ADDRSTRLEN)) {
				printf("Destination Ip Address is %s \n",currentPosition->destinationIPAddress);
				printf("Destination socket Id is %d \n",currentPosition->socketId);
				return currentPosition->socketId;
			}
			currentPosition = currentPosition->next;
		}
	}

	return 0;
}


int getHopCountForROute(char destinationAddress[INET_ADDRSTRLEN]) {
	deleteTimeoutEnries();
	routeEntry* currentPosition = routeTableHead;
	if(routeTableHead == NULL) {
		return 0;
	}
	else  {
		while(currentPosition != NULL) {
			if(!strncmp(currentPosition->destinationIPAddress,destinationAddress,6)) {
				return currentPosition->hopcount;

			}
			currentPosition = currentPosition->next;
		}
	}
	return 0;
}


void populateDestMacAddressForRoute(char destinationAddress[INET_ADDRSTRLEN], char destMacAddress [HADDR_LEN]) {
	routeEntry* currentPosition = routeTableHead;
	if(routeTableHead == NULL) {
		return ;
	}
	else  {
		while(currentPosition != NULL) {
			if(!strncmp(currentPosition->destinationIPAddress,destinationAddress,HADDR_LEN)) {
				memcpy(destMacAddress,currentPosition->destinationMACAddress,HADDR_LEN);

			}
			currentPosition = currentPosition->next;
		}
	}

	return;
}

int getHopCountIfRouteExist(char destinationIpAddress[INET_ADDRSTRLEN]) {
	routeEntry* currentPosition = routeTableHead;
	if(routeTableHead == NULL) {
		return 0;
	}
	else  {
		while(currentPosition != NULL) {
			if(!strncmp(currentPosition->destinationIPAddress,destinationIpAddress,INET_ADDRSTRLEN)) {
				return currentPosition->hopcount;

			}
			currentPosition = currentPosition->next;
		}
	}

	return 0;
}

