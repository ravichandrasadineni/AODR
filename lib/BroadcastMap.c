/*
 * BroadCastMap.c
 *
 *  Created on: Nov 10, 2014
 *      Author: ravichandrasadineni
 */
#include "BroadcastMap.h"

bList* bListHead = NULL;
bList* bListTail = NULL;

int isObselete( char ipAddress[INET_ADDRSTRLEN], int brodcastId) {
	if(bListHead  == NULL)
		return 0;
	bList* currentBrdElement = bListHead;
	while(currentBrdElement !=NULL) {
		if(!strncmp(currentBrdElement->sourceAddr,ipAddress,INET_ADDRSTRLEN)) {
			printf("BroadcastMap.c: source address in table is %s \n",currentBrdElement->sourceAddr );
			printf("BroadcastMap.c: current ip address is %s \n",ipAddress);
			if(currentBrdElement->brodcastId >= brodcastId) {
				return 1;
			}
		}
		currentBrdElement = currentBrdElement->next;
	}
	return 0;
}

int isSameBroadCastId( char ipAddress[INET_ADDRSTRLEN], int brodcastId) {
	if(bListHead  == NULL)
		return 0;
	bList* currentBrdElement = bListHead;
	while(currentBrdElement !=NULL) {
		if(!strncmp(currentBrdElement->sourceAddr,ipAddress,INET_ADDRSTRLEN)) {
			if(currentBrdElement->brodcastId == brodcastId) {
				return 1;
			}
		}
		currentBrdElement = currentBrdElement->next;
	}
	return 0;
}


void deleteExistingEntry(char ipaddress[INET_ADDRSTRLEN], int brodcastId) {
	if(bListHead  == NULL)
		return ;
	bList* currentBrdElement = bListHead;
	bList* prevBrdElement = NULL;
	while(currentBrdElement !=NULL) {
		if(!strncmp(currentBrdElement->sourceAddr,ipaddress,INET_ADDRSTRLEN)) {
			if(currentBrdElement->brodcastId > brodcastId) {
				printf("BroadCastMap.c :current broadcast id is %d \n",currentBrdElement->brodcastId);
				printf("BroadCastMap.c :broadcast id in the received packet is  %d \n",brodcastId);
				printf("BrodCastMap.c : DELETE CALLED TO DELETE ADVANCED BRODCAST PACKET INFO\n");
				exit(1);
			}
			if(prevBrdElement == NULL) {
				bListHead = currentBrdElement->next;
				if(bListHead  == NULL)
					bListTail = NULL;
				free(currentBrdElement);
			}
			else if(currentBrdElement->next == NULL) {
				bListTail = prevBrdElement;
				bListTail->next= NULL;
				free(currentBrdElement);
			}
			else {
				prevBrdElement->next = currentBrdElement->next;
				free(currentBrdElement);
			}
		}
		prevBrdElement = currentBrdElement;
		currentBrdElement = currentBrdElement->next;

	}
	return ;

}
int addToBroadCastList( char souceAddr[INET_ADDRSTRLEN], int brodcastId) {
	deleteExistingEntry( souceAddr,  brodcastId);

	if(bListHead  == NULL) {
		bListHead = (bList *)allocate_void(sizeof(bList));
		bListTail = bListHead;
	}
	else {
		bListTail->next = (bList *)allocate_void(sizeof(bList));
		bListTail = bListTail->next;
	}
	strncpy(bListTail->sourceAddr,souceAddr,INET_ADDRSTRLEN);
	bListTail->brodcastId = brodcastId;
	bListTail->next =NULL;
}

