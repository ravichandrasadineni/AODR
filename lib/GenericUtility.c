/*
 * GenericUtility.c
 *
 *  Created on: Nov 8, 2014
 *      Author: ravichandrasadineni
 */

#include "GenericUtility.h"

void getDomainName(char* ipAddressString, char* domainName) {
	struct hostent *he;
	struct in_addr ipAddress;
	inet_pton(AF_INET, ipAddressString, &ipAddress);
	he = gethostbyaddr(&ipAddress, sizeof(ipAddress), AF_INET);
	if(he == NULL)  {
		printf(" No valid DomainName for the given IpAddress: %s \n",ipAddressString);
		exit(1);
	}
	strncpy(domainName,he->h_name,strlen(he->h_name));
}

void getUserChoice(char choice[5]) {

	while(1) {
		printf("Please enter the VM to connect to \n");
		scanf("%s",choice);
		return;
	}
}

void intTochar( int number, char* string) {
	snprintf(string, 10,"%d",number);
}


void printMacAddress (char haddr[HADDR_LEN]) {
	int i;
	for (i=0; i<5; i++) {
		printf ("%02x:", haddr[i]);
	}
	printf ("%02x\n",haddr[5]);
}


void printFrame(ODRFrame receivedFrame){
	char hostname[1024],sourceHost[1024],destHost[1024];
	memset(hostname,'\0',1024);
	memset(sourceHost, '\0', 1024);
	memset(destHost, '\0', 1024);
	gethostname(hostname,1023);
	getDomainName(receivedFrame.data.source, sourceHost);
	getDomainName(receivedFrame.data.destination, destHost);
	printf("ODR at node %s : sending frame hdr src %s dest ",hostname, hostname);
	printMacAddress(receivedFrame.header.destAddress);
	printf("\t\tODR msg type %d src %s dest %s \n",receivedFrame.header.packetType, sourceHost, destHost);
}
//void printFrame (ODRFrame receivedFrame) {
//	printf("DMA :");
//	printMacAddress(receivedFrame.header.destAddress);
//	printf("SMA:");
//	printMacAddress(receivedFrame.header.sourceAddress);
//	printf("PTYP :%d \t",receivedFrame.header.packetType);
//	printf("HOPC:%d \t",receivedFrame.header.hopcount);
//	printf("BID:%d \t",receivedFrame.header.Broadcastid);
//	printf("RREPS:%d \t",receivedFrame.header.RREPSent);
//	printf("SIP:%s \t",receivedFrame.data.source);
//	printf("DIP:%s \t",receivedFrame.data.destination);
//	printf("SP:%d \t",receivedFrame.data.sourcePort);
//	printf("DP:%d \t",receivedFrame.data.destinationPort);
//	printf("FR :%d \t",receivedFrame.data.forceRoute);
//	printf("Message:%s \n",receivedFrame.data.message);
//
//}


