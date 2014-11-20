/*
 * RREPManager.h
 *
 *  Created on: Nov 19, 2014
 *      Author: harsha
 */

#ifndef LIB_ODRRREPMANAGER_H_
#define LIB_ODRRREPMANAGER_H_
#include "ODRRoutingTable.h"
#include "AddressUtility.h"
#include "unp.h"
#include "ODRDataPacketManager.h"
#include "FrameSendRecvUtility.h"
#include "ODRsocketUtility.h"
#include "ODRRoutingTable.h"
void handleRREP(ODRFrame currentFrame,int setSocket,int *ifSockets,int numOFInf);


#endif /* LIB_ODRRREPMANAGER_H_ */
