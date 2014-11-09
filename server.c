/*
 * server.c
 *
 *  Created on: Nov 9, 2014
 *      Author: ravichandrasadineni
 */

#include "unp.h"
#include "lib/UDSUtility.h"
#include "lib/AddressUtility.h"



void printRequest(char* clientIp) {
	char domainName[256];
	char localHostname[1024];
	gethostname(localHostname, 1023);
	memset(domainName,'\0', 256);
	getDomainName(clientIp,domainName);
	printf("server at node   %s  responding to request from   %s \n",localHostname,domainName);

}
int main (int argc, char* argv) {
	int sockfd;
	char clientMessage[MAXLINE];
	char serverReply[MAXLINE];
	char clientIp[INET_ADDRSTRLEN];
	int clientPort =0;
	sockfd = getServerBindedsocket();
	connectToODR(sockfd);
	while(1) {
		msg_recv(sockfd,clientMessage,clientIp,&clientPort);
		printRequest(clientIp);
		msg_send(sockfd,clientIp,clientPort,clientMessage,0);
		memset(clientMessage, '\0',MAXLINE);
	}

}
