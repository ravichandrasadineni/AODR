/*
 * GenericUtility.c
 *
 *  Created on: Nov 8, 2014
 *      Author: ravichandrasadineni
 */

#include "GenericUtility.h"



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

void printFrame (ODRFrame receivedFrame) {
	printf("DMA :");
	printMacAddress(receivedFrame.header.destAddress);
	printf("SMA:");
	printMacAddress(receivedFrame.header.sourceAddress);
	printf("PTYP :%d \t",receivedFrame.header.packetType);
	printf("HOPC:%d \t",receivedFrame.header.hopcount);
	printf("BID:%d \t",receivedFrame.header.Broadcastid);
	printf("RREPS:%d \t",receivedFrame.header.RREPSent);
	printf("SIP:%s \t",receivedFrame.data.source);
	printf("DIP:%s \t",receivedFrame.data.destination);
	printf("SP:%d \t",receivedFrame.data.sourcePort);
	printf("DP:%d \t",receivedFrame.data.destinationPort);
	printf("FR :%d \t",receivedFrame.data.forceRoute);
	printf("Message:%s \n",receivedFrame.data.message);

}


