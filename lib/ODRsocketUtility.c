/*
 * ODRsocketUtility.c
 *
 *  Created on: Nov 9, 2014
 *      Author: ravichandrasadineni
 */
#include "ODRsocketUtility.h"


int isEth0(char* name) {
	if( strncmp(ETHERNET0,name,16)) {
		return 1;
	}
	return 0;
}

struct sockaddr_ll getODRBindedSocket(int sockfd) {
	struct sockaddr_ll odrSocket;
	int sockLen;
	if(getsockname(sockfd, (SA*)&odrSocket	,&sockLen)<0) {
		perror("Failed to UNLINK temperory FIle ");
		exit(1);
	}
	return odrSocket;
}

int createNewSocket() {
	int s = socket(PF_PACKET, SOCK_RAW,htons(atoi(ETH_TYPE)));
	if(s == -1) {
		perror("socket Error: ");
		exit(0);
	}
	return s;
}


void getListOfInterfaces(ifInfo* ifList, int* size ) {
	struct hwa_info	*hwa, *hwahead;
	struct sockaddr	*sa;
	char   *ptr;
	int    i, prflag;
	ifList = NULL;
	size=0;
	ifInfo* currentPosition;
	for (hwahead = hwa = Get_hw_addrs(); hwa != NULL; hwa = hwa->hwa_next) {
		if (isEth0(hwa->if_name)) {
			continue;
		}
		if(ifList == NULL) {
			ifList = (ifInfo *)allocate_void(sizeof(ifInfo));
			currentPosition = ifList;
		}
		else {
			currentPosition->next = (ifInfo *)allocate_void(sizeof(ifInfo));
			currentPosition = currentPosition->next;
		}
		(*size)++;
		strncpy(currentPosition->if_haddr,hwa->if_haddr,HADDR_LEN);
		currentPosition->if_index = hwa->if_index;
	}
	free_hwa_info(hwahead);
}

void createAndBindSocketsTOInterfaces(int* sockets, int* number) {
	ifInfo ifList;
	int size;
	getListOfInterfaces(&ifList,&size);
	sockets = allocate_intmem(size);
	(*number) = size;
	int i;
	for(i=0;i<size; i++) {
		int sockfd = createNewSocket();
		struct sockaddr_ll sADDR;
		sADDR.sll_ifindex =ifList.if_index ;
		if(bind(sockfd,(SA*)&sADDR,sizeof(sADDR)) <0) {
			perror("BINDING SOCKET TO INTERFACE FAILED :");
			exit(1);
		}
		sockets[i]= sockfd;
	}

	return;
}


