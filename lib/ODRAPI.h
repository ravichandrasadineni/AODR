/*
 * ODRAPI.h
 *
 *  Created on: Nov 8, 2014
 *      Author: ravichandrasadineni
 */

#ifndef ODRAPI_H_
#define ODRAPI_H_

#include "unp.h"
#include "GenericUtility.h"

int msg_send(int sockfd, char destination[INET_ADDRSTRLEN],int port, char* message, int forceRoute );
int msg_recv(int sockfd,  char* message, char source[INET_ADDRSTRLEN], int *port);



#endif /* ODRAPI_H_ */
