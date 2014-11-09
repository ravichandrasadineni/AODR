/*
 * UDSUtility.h
 *
 *  Created on: Nov 8, 2014
 *      Author: ravichandrasadineni
 */

#ifndef UDSUTILITY_H_
#define UDSUTILITY_H_
#include "unp.h"
#include "ODRConstants.h"
#include <stdio.h>
void connectToODR(int sockfd);
void connectToTimeClientServer(int sockfd);
int getclientBindedsocket();
int getServerBindedsocket();
void unLinkSocket(int sockFd);

#endif /* UDSUTILITY_H_ */
