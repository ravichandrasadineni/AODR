/*
 * server.c
 *
 *  Created on: Nov 9, 2014
 *      Author: ravichandrasadineni
 */

#include "unp.h"
#include "lib/UDSUtility.h"
#include "lib/AddressUtility.h"
#include "lib/GenericUtility.h"


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
	time_t currentTime;
	DataPacket recvPacket, sendPacket;
	populateLocalAddress(sendPacket.source);
	sockfd = getServerBindedsocket();
	connectToODR(sockfd);
	while(1) {
		msg_recv(sockfd,&recvPacket, NULL);
		printRequest(recvPacket.source);
		strncpy(sendPacket.source,recvPacket.destination,INET_ADDRSTRLEN);
		sendPacket.sourcePort = recvPacket.destinationPort;
		strncpy(sendPacket.destination,recvPacket.source,INET_ADDRSTRLEN);
		sendPacket.destinationPort = recvPacket.sourcePort;
		sendPacket.forceRoute = recvPacket.forceRoute;
		 time(&currentTime);
		strncpy(sendPacket.message, ctime(&currentTime), FRAME_BUFFER_LENGTH);
		msg_send(sockfd,sendPacket);
	}

}
