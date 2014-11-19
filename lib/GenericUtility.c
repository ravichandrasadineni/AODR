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
	printf("Destination  Mac Address :");
	printMacAddress(receivedFrame.header.destAddress);
	printf("Source Mac Address :");
	printMacAddress(receivedFrame.header.sourceAddress);
	printf("PACKET TYPE :%d \n",receivedFrame.header.packetType);
	printf("HOP COUNT:%d \n",receivedFrame.header.hopcount);
	printf("BROADCAST ID:%d \n",receivedFrame.header.Broadcastid);
	printf("SOURCE IP:%s \n",receivedFrame.data.source);
	printf("Destination IP:%s \n",receivedFrame.data.destination);
	printf("Source Port:%d \n",receivedFrame.data.sourcePort);
	printf("Destination Port:%d \n",receivedFrame.data.destinationPort);
	printf("Fource Route :%d \n",receivedFrame.data.forceRoute);
	printf("Message:%s \n",receivedFrame.data.message);

}


