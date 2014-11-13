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
	printf("Server.c : server at node   %s  responding to request from   %s \n",localHostname,domainName);
}





int main (int argc, char* argv) {
	int sockfd;
	char clientMessage[MAXLINE];
	char serverReply[MAXLINE];
	char localServerAddress[INET_ADDRSTRLEN];
	char clientIp[INET_ADDRSTRLEN];
	int clientPort =0;
	populateLocalAddress(localServerAddress);
	sockfd = getServerBindedsocket();
	//connectToODR(sockfd);
	while(1) {
		msg_recv(sockfd,clientMessage,clientIp,NULL,&clientPort, NULL);
		printRequest(clientIp);
		msg_send(sockfd,localServerAddress,clientIp,clientPort,clientMessage,0);
		memset(clientMessage, '\0',MAXLINE);
	}

}
