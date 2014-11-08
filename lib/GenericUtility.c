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
