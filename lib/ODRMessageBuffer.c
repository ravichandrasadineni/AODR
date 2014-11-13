/*
 * ODRMessageBuffer.c
 *
 *  Created on: Nov 12, 2014
 *      Author: ravichandrasadineni
 */
#include "ODRMessageBuffer.h"

int timeOutSecs =0;
DataPacket buffer[DATAPACKET_BUFFER_SIZE];
int currentSize =0;
void intializeBufferTimeOut(int timeOut) {
	timeOutSecs = timeOut;
}

void parkIntoBuffer(DataPacket packet) {
	buffer[currentSize] = packet;
	currentSize ++;
}

void sendPacket(DataPacket packet)  {

}
