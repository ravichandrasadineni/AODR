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
		printf("ODRRREQMANAGER.C : Only one interface for the node\n");
		return 0;
	}
	// If the route doesn't exist for the source router.  forward
	if (!doesRouteExist(currentFrame.data.source)) {
		printf("ODRRREQMANAGER.C : ROUTE does not exist for the destination \n");
		return 1;
	}

	// If the hopCount for the source  is less. forward
	int hopCount = getHopCountForROute(currentFrame.data.source);
	if (hopCount >= (currentFrame.header.hopcount - 1)) {
		printf("ODRRREQMANAGER.C : Old route has same or less hop count than current Route\n");
	} else {
		printf("ODRRREQMANAGER.C : Heard a better route to source\n");
		return 1;

	}

	// If I am the destination router.  don't forward
	char localAddress[INET_ADDRSTRLEN];
	populateLocalAddress(localAddress);
	if (!strcmp(localAddress, currentFrame.data.destination)) {
		printf("ODRRREQMANAGER.C : RREQ DESTINED TO ME\n");
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
	// If the route does not exist for the destination router.
	else if (!doesRouteExist(currentFrame.data.destination)) {
		return 1;
	}
	return 0;

}

int shouldSendRREP(ODRFrame currentFrame) {
	// If RREP already sent, don't bother
	if (currentFrame.header.RREPSent == 1) {
		printf("ODRRREQMANAGER.C : RREP Sent set to 1 in the received packet \n");
		return 0;
	}

	// If I am the destination router.  send RREP
	char localAddress[INET_ADDRSTRLEN];
	populateLocalAddress(localAddress);
	if (!strcmp(localAddress, currentFrame.data.destination)) {
		printf("ODRRREQMANAGER.C : RREQ destined to me\n");

		return 1;
	}
	// If route exist
	if (doesRouteExist(currentFrame.data.destination)) {
		// If force route set. Don't bother since you are not the destination
		if (currentFrame.data.forceRoute == 1) {
			printf("ODRRREQMANAGER.C : FORCE ROUTE SET TO 1\n");
			return 0;
		}
		// send a RREP otherwise
		else {
			return 1;
		}
	}

	return 0;
}

void sendRREP(int listenedSocket, ODRFrame currentFrame) {
	char tempIpAddress[INET_ADDRSTRLEN];
	char tempMacAddress[INET_ADDRSTRLEN];
	char sourceMacAddress[INET_ADDRSTRLEN];
	int tempport;
	strncpy(tempIpAddress, currentFrame.data.source, INET_ADDRSTRLEN);
	strncpy(currentFrame.data.source, currentFrame.data.destination,
			INET_ADDRSTRLEN);
	getSourceMacForInterface(listenedSocket, sourceMacAddress);
	strncpy(currentFrame.data.destination, tempIpAddress, INET_ADDRSTRLEN);
	memcpy(tempMacAddress, currentFrame.header.sourceAddress, HADDR_LEN);
	memcpy(currentFrame.header.sourceAddress, sourceMacAddress,
			HADDR_LEN);
	memcpy(currentFrame.header.destAddress, tempMacAddress, HADDR_LEN);
	tempport = currentFrame.data.sourcePort;
	currentFrame.data.sourcePort = currentFrame.data.destinationPort;
	currentFrame.data.destinationPort = tempport;
	// NEW RREP SETTING HOP COUNT TO 0
	currentFrame.header.hopcount = 0;
	char* rrepFrame = buildRREP(currentFrame);
	send_rawpacket(listenedSocket,rrepFrame);
	free(rrepFrame);
}

void handleRREQ(ODRFrame currentFrame, int listenedSocket, int *ifSockets,
		int numOFInf) {
	if(isObselete(currentFrame.data.source,currentFrame.header.Broadcastid)) {
		printf("ODRRREQMANAGER.C : Obselete RREQ Packet,Ignoring\n");
		return;
	}
	printf("ODRRREQMANAGER.C : Recieved RREQ \n");
	if (shouldSendRREP(currentFrame)) {
		printf("ODRRREQMANAGER.C : sending RREP\n");

		sendRREP(listenedSocket, currentFrame);
	}
	if (shoudForwardRREQ(currentFrame, numOFInf)) {
		if (shouldSendRREP(currentFrame)) {
			printf("ODRRREQMANAGER.C : RREPSent set to 1 \n");
			currentFrame.header.RREPSent = 1;
		}
		printf("ODRRREQMANAGER.C : sending RREQ on all other interfaces\n");
		sendRREQonOtherInterfaces(currentFrame, listenedSocket, ifSockets,
				numOFInf);
	}

}

