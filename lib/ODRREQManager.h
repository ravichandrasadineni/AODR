/*
 * ODRREQManager.h
 *
 *  Created on: Nov 19, 2014
 *      Author: ravichandrasadineni
 */

#ifndef LIB_ODRREQMANAGER_H_
#define LIB_ODRREQMANAGER_H_

#include "GenericUtility.h"
#include "ODRConstants.h"
#include "AddressUtility.h"
#include "FrameBufferUtility.h"
#include "BroadcastMap.h"
void handleRREQ(ODRFrame currentFrame, int listenedSocket, int *ifSockets,int numOFInf);
#endif /* LIB_ODRREQMANAGER_H_ */
