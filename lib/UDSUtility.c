/*
 * UDSUtility.c
 *
 *  Created on: Nov 8, 2014
 *      Author: ravichandrasadineni
 */

#include "UDSUtility.h"
#include "ODRConstants.h"

int getclientBindedsocket() {
	int sockfd, fileFd;
	char nameBuff[32];
	struct sockaddr_un cliaddr;
	bzero(&cliaddr, sizeof(cliaddr));
	sockfd = socket(AF_LOCAL,SOCK_DGRAM,0);
	if(sockfd < 0) {
		perror("unable to create client Unix Domain Socket :");
		exit(0);
	}
	memset(nameBuff,0,sizeof(nameBuff));

	strncpy(nameBuff,ODR_CLIENT_PRE ,FILE_NAME_LENGTH);
	mkstemp(nameBuff);
//	printf("UDSUtility.c :nameBuff is %s \n",nameBuff);
	unlink(nameBuff);
	cliaddr.sun_family = AF_LOCAL;
	strncpy(cliaddr.sun_path,nameBuff,strlen(nameBuff));
//	printf("UDSUtility.c :cliaddr.sun_path is %s \n",cliaddr.sun_path);
	if(bind(sockfd,(SA *)&cliaddr, sizeof(cliaddr))<0) {
		perror("Failed to Bind Unix Domain Socket :");
		exit(0);
	}
	return sockfd;
}

int getServerBindedsocket() {
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
	strncpy(nameBuff,TIME_SERVER,FILE_NAME_LENGTH);
	unlink(nameBuff);
	servaddr.sun_family = AF_LOCAL;
	strncpy(servaddr.sun_path,nameBuff,strlen(nameBuff));
	if(bind(sockfd,(SA *)&servaddr, sizeof(servaddr))<0) {
		perror("Failed to Bind Unix Domain Socket :");
		exit(0);
	}
	return sockfd;
}

void unLinkSocket(int sockFd) {
	struct sockaddr_un unixSocket;
	int sockLen;
	if(getsockname(sockFd, (SA*)&unixSocket	,&sockLen)<0) {
		perror("Failed to UNLINK temporary FIle ");
		return;
	}
	remove(unixSocket.sun_path);
	return;
}

void connectTO (int sockfd, char*fileName) {
	struct sockaddr_un servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
	strncpy(servaddr.sun_path,fileName, strlen(fileName));
	if(connect(sockfd,(SA *)&servaddr, sizeof(servaddr))<0) {
		perror("UDSUtility.C:Failed to connect Unix Domain Socket  :");
		unLinkSocket(sockfd);
		exit(0);
	}
}

void connectToODR(int sockfd) {
	connectTO(sockfd,ODR_SERVER);

}

void connectToTimeClientServer(int sockfd) {
	connectTO(sockfd,TIME_SERVER);
}


