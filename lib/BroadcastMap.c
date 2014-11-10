/*
 * BroadCastMap.c
 *
 *  Created on: Nov 10, 2014
 *      Author: ravichandrasadineni
 */
#include "BroadcastMap.h"

bList* bListHead = NULL;
bList* bListTail = NULL;

int isObselete( char hrdAddr[HADDR_LEN], int brodcastId) {
	if(bListHead  == NULL)
		return 0;
	bList* currentBrdElement = bListHead;
	while(currentBrdElement !=NULL) {
		if(!strncmp(currentBrdElement->brodcastAddr,hrdAddr,HADDR_LEN)) {
			if(currentBrdElement->brodcastId >= brodcastId) {
				return 1;
			}
		}
		currentBrdElement = currentBrdElement->next;
	}
	return 0;

}
void deleteExistingEntry(char hrdAddr[HADDR_LEN], int brodcastId) {
	if(bListHead  == NULL)
		return ;
	bList* currentBrdElement = bListHead;
	bList* prevBrdElement = NULL;
	while(currentBrdElement !=NULL) {
		if(!strncmp(currentBrdElement->brodcastAddr,hrdAddr,HADDR_LEN)) {
			if(currentBrdElement->brodcastId > brodcastId) {
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
int addToBroadCastList( char hrdAddr[HADDR_LEN], int brodcastId) {
	deleteExistingEntry( hrdAddr,  brodcastId);

	if(bListHead  == NULL) {
		bListHead = (bList *)allocate_void(sizeof(bList));
		bListTail = bListHead;
	}
	else {
		bListTail->next = (bList *)allocate_void(sizeof(bList));
		bListTail = bListTail->next;
	}
	strncpy(bListTail->brodcastAddr,hrdAddr,HADDR_LEN);
	bListTail->brodcastId = brodcastId;
	bListTail->next =NULL;
}

