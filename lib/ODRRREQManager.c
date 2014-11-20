/*
 * ODRRREQManager.c
 *
 *  Created on: Nov 19, 2014
 *      Author: ravichandrasadineni
 */
#include "ODRREQManager.h"

int shoudForwardRREQ(ODRFrame currentFrame, int numOFInf) {
	// IF only interface don't bother to forward
	if (numOFInf == 1) {
		return 0;
	}
	// If the route doesn't exist for the source router.  forward
	if (!doesRouteExist(currentFrame.data.source)) {
		return 1;
	}

	// If the hopCount for the source  is less. forward
	int hopCount = getHopCountForROute(currentFrame.data.source);
	if (hopCount > (currentFrame.header.hopcount - 1)) {
		return 1;
	}

	// If I am the destination router.  don't forward
	char localAddress[INET_ADDRSTRLEN];
	populateLocalAddress(localAddress);
	if (!strcmp(localAddress, currentFrame.data.destination)) {
		return 0;
	}

	// If the route exist for the destination router.
	if (doesRouteExist(currentFrame.data.destination)) {
		// If fource route set. forward
		if (currentFrame.data.forceRoute == 1) {
			return 1;
		}
		//otherwise don't forward
		return 0;
	}
	return 0;

}

int shouldSendRREP(ODRFrame currentFrame) {
	// If RREP already sent, don't bother
	if (currentFrame.header.RREPSent == 1) {
		return 0;
	}

	// If I am the destination router.  send RREP
	char localAddress[INET_ADDRSTRLEN];
	populateLocalAddress(localAddress);
	if (!strcmp(localAddress, currentFrame.data.destination)) {
		return 1;
	}
	// If route exist
	if (doesRouteExist(currentFrame.data.destination)) {
		// If force route set. Don't bother since you are not the destination
		if (currentFrame.data.forceRoute == 1) {
			return 0;
		}
		// send a RREP otherwise
		else {
			return 1;
		}
	}

	return 0;
}

void sendRREP(ODRFrame currentFrame) {
	char tempIpAddress[INET_ADDRSTRLEN];
	char tempMacAddress[INET_ADDRSTRLEN];
	int tempport;
	strncpy(tempIpAddress, currentFrame.data.source, INET_ADDRSTRLEN);
	strncpy(currentFrame.data.source, currentFrame.data.destination,
			INET_ADDRSTRLEN);
	strncpy(currentFrame.data.destination, tempIpAddress, INET_ADDRSTRLEN);
	memcpy(tempMacAddress, currentFrame.header.sourceAddress, HADDR_LEN);
	memcpy(currentFrame.header.sourceAddress, currentFrame.header.destAddress,
			HADDR_LEN);
	memcpy(currentFrame.header.destAddress, tempMacAddress, HADDR_LEN);
	tempport = currentFrame.data.sourcePort;
	currentFrame.data.sourcePort = currentFrame.data.destinationPort;
	currentFrame.data.destinationPort = tempport;
	if (!doesRouteExist(currentFrame.data.destination)) {
		printf(
				"ODRREQMANanager.c : something teribilly wrong. No Route for Rrep \n");
		exit(0);
	}
	int outgoingSocket = getOutInfForDest(currentFrame.data.destination);
	char* rrepFrame = buildRREP(currentFrame);
	send_rawpacket(outgoingSocket,rrepFrame);
}

void handleRREQ(ODRFrame currentFrame, int listenedSocket, int *ifSockets,
		int numOFInf) {
	if (shouldSendRREP(currentFrame)) {
		sendRREP(currentFrame);
	}
	if (shoudForwardRREQ(currentFrame, numOFInf)) {
		if (shouldSendRREP(currentFrame)) {
			currentFrame.header.RREPSent = 1;
		}
		sendRREQonOtherInterfaces(currentFrame, listenedSocket, ifSockets,
				numOFInf);
	}

}

