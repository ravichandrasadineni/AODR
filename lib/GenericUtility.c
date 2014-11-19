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



