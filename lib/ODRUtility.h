/*
 * ODRUtility.h
 *
 *  Created on: Nov 11, 2014
 *      Author: ravichandrasadineni
 */

#ifndef LIB_ODRUTILITY_H_
#define LIB_ODRUTILITY_H_

#include "unp.h"
#include "ODRConstants.h"

void getListeningSet(fd_set *readSet,int *maxfd, int* ifSockets, int count, int UDSsocket);
int getTimeOut(int argc, char*argv[]) ;

#endif /* LIB_ODRUTILITY_H_ */