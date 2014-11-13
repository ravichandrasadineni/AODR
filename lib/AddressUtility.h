/*
 * AddressUtility.h
 *
 *  Created on: Nov 8, 2014
 *      Author: ravichandrasadineni
 */

#ifndef ADDRESSUTILITY_H_
#define ADDRESSUTILITY_H_
#include "unp.h"
#include <stdio.h>

void getIpAddressFromDomainName(char* string, char* ipAddress) ;
void getDomainName(char* ipAddressString, char* domainName);
void populateLocalAddress(char localAddress[INET_ADDRSTRLEN]);




#endif /* ADDRESSUTILITY_H_ */
