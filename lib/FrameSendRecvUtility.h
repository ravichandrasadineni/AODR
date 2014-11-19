/*
 * FrameSendRecvUtility.h
 *
 *  Created on: Nov 16, 2014
 *      Author: ravichandrasadineni
 */

#ifndef LIB_FRAMESENDRECVUTILITY_H_
#define LIB_FRAMESENDRECVUTILITY_H_

#include "unp.h"
#include "ODRConstants.h"

void send_rawpacket (int raswSock, unsigned char * frame);

int recv_rawpacket(int rawsock, unsigned char *pkt);




#endif /* LIB_FRAMESENDRECVUTILITY_H_ */
