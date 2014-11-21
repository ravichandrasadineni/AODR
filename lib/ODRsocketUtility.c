/*
 * ODRsocketUtility.c
 *
 *  Created on: Nov 9, 2014
 *      Author: ravichandrasadineni
 */
#include "ODRsocketUtility.h"

int sockInfMapsize =0;
interfaceSock sockToInfMapper[10];

void  getSourceMacForInterface(int sockFd, char sourceMac[HADDR_LEN] ) {
	int i=0;
	memset(sourceMac,'\0',HADDR_LEN);
	for(i=0; i < sockInfMapsize; i++) {
		if(sockToInfMapper[i].sockfd == sockFd) {
			memcpy(sourceMac,sockToInfMapper[i].sourceMac,HADDR_LEN);
			return;
		}
	}

}

int isEth0OrLoopback(char* name) {
	if(!strncmp(ETHERNET0,name,16)) {
		return 1;
	}
	if(!strncmp(LOOPBACKIF,name,16)) {
		return 1;
	}

	return 0;
}


int createNewSocket() {
	int s = socket(PF_PACKET, SOCK_RAW,htons(ETH_TYPE));
	if(s == -1) {
		perror("socket Error: ");
		exit(0);
	}
	return s;
}


void getListOfInterfaces(ifInfo** ifList, int* size ) {
	struct hwa_info	*hwa, *hwahead;
	struct sockaddr	*sa;
	char   *ptr;
	int    i, prflag;
	(*ifList) = NULL;
	(*size)=0;
	ifInfo* currentPosition;
	for (hwahead = hwa = Get_hw_addrs(); hwa != NULL; hwa = hwa->hwa_next) {
		if (isEth0OrLoopback(hwa->if_name)) {
			continue;
		}
		if((*ifList) == NULL) {
			(*ifList)  = (ifInfo *)allocate_void(sizeof(ifInfo));
			currentPosition = (*ifList) ;
		}
		else {
			currentPosition->next = (ifInfo *)allocate_void(sizeof(ifInfo));
			currentPosition = currentPosition->next;
		}
		(*size)++;
		memcpy(currentPosition->if_haddr,hwa->if_haddr,HADDR_LEN);
		currentPosition->if_index = hwa->if_index;
	}
	free_hwa_info(hwahead);
}

void createAndBindSocketsTOInterfaces(int** sockets, int* number) {
	ifInfo* ifList;
	int size;
	getListOfInterfaces(&ifList,&size);
	(*sockets) = allocate_intmem(size);
	(*number) = size;
	int i;
	for(i=0;i<size; i++) {
		int sockfd = createNewSocket();
		struct sockaddr_ll sADDR;
		memset(&sADDR,'\0', sizeof(sADDR));
		sADDR.sll_ifindex =ifList->if_index ;
		sADDR.sll_halen = ETH_ALEN;
		sADDR.sll_protocol = htons(ETH_TYPE);
		sADDR.sll_family = PF_PACKET;
		if(bind(sockfd,(SA*)&sADDR,sizeof(sADDR)) <0) {
			perror("BINDING SOCKET TO INTERFACE FAILED :");
			exit(1);
		}
		sockToInfMapper[sockInfMapsize].sockfd = sockfd;
		memcpy(sockToInfMapper[sockInfMapsize].sourceMac,ifList->if_haddr,HADDR_LEN);
		(*sockets)[i]= sockfd;
		ifList = ifList->next;
		printf("%d ------>", sockToInfMapper[sockInfMapsize].sockfd);
		printMacAddress(sockToInfMapper[sockInfMapsize].sourceMac);
		sockInfMapsize++;
	}

	return;
}

int createAndBindUDS() {

	int sockfd, fileFd;
	char nameBuff[32];
	struct sockaddr_un servaddr;
	bzero(&servaddr, sizeof(servaddr));
	sockfd = socket(AF_LOCAL,SOCK_DGRAM,0);
	if(sockfd < 0) {
		perror("unable to create client Unix Domain Socket :");
		exit(0);
	}
	memset(nameBuff,0,sizeof(nameBuff));
	strncpy(nameBuff,ODR_SERVER,25);
	unlink(nameBuff);
	servaddr.sun_family = AF_LOCAL;
	strncpy(servaddr.sun_path,nameBuff,strlen(nameBuff));
	if(bind(sockfd,(SA *)&servaddr, sizeof(servaddr))<0) {
		perror("Failed to Bind Unix Domain Socket :");
		exit(0);
	}
	return sockfd;
}
