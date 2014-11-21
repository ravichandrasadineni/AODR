
#include "lib/ODRDataPacketManager.h"
#include "lib/ODRsocketUtility.h"
#include "lib/ODRUtility.h"
#include "lib/ODRRoutingTable.h"


int getSetSocket(int *ifSockets, int numOfInf, fd_set *readSet) {
	int i;
	for(i=0; i<numOfInf;i++) {
		if(FD_ISSET(ifSockets[i],readSet)) {
			return ifSockets[i];
		}
	}
	return -1;
}

int shoudAddRoute(ODRFrame currentFrame) {
	if(currentFrame.header.packetType == PACKET_MSG) {
		return 1;
	}
	// If packet is destined to me then the route should have been already added
	// Else Add the route
	if(currentFrame.header.packetType == PACKET_RREP) {
		char localAddress[INET_ADDRSTRLEN];
		populateLocalAddress(localAddress);
		if (!strncmp(currentFrame.data.destination,localAddress, INET_ADDRSTRLEN)) {
			return 0;
		}
		return 1;
	}
	printf("ODR.C :Before checking RREQ condition \n");
	// ONLY RREQ LEFT
	if(!isObselete(currentFrame.data.source,currentFrame.header.Broadcastid)) {
		printf("ODR.C : RREQ  adding route \n");
		return 1;
	}
	if(isSameBroadCastId(currentFrame.data.source,currentFrame.header.Broadcastid)) {
		int currentHopCount = getHopCountForROute(currentFrame.header.sourceAddress);
		if(currentHopCount  > currentFrame.header.hopcount){
			return 1;
		}
	}
	printf("ODR.C :RREQ is obselete \n");
	return 0;

}


int main(int argc,char *argv[]){
	int *ifSockets, numOFInf, udsSocket;
	createAndBindSocketsTOInterfaces(&ifSockets,&numOFInf);
	udsSocket = createAndBindUDS();
	int timeOutSecs = getTimeOut(argc, argv);
	setExpiryTimeForRoutingTable(timeOutSecs);
	initializeportMap(timeOutSecs);
	fd_set readSet;
	int maxfd;
	while(1) {
		getListeningSet(&readSet,&maxfd,ifSockets,numOFInf,udsSocket);
		if((select(maxfd,&readSet,NULL,NULL,NULL))<0) {
			perror("Select on ODR FAILED");
		}
		if (FD_ISSET(udsSocket,&readSet)) {
			DataPacket  currentDataPacket;
			struct sockaddr_un cliaddr;
			currentDataPacket = getData(udsSocket, &cliaddr);
			currentDataPacket.sourcePort = generatePortNumber(cliaddr.sun_path);
			sendDataPacket(currentDataPacket,udsSocket,ifSockets,numOFInf);

		}
		else {
			int setSocket = getSetSocket(ifSockets, numOFInf,&readSet);
			char *newFrame = allocate_strmem(FRAME_LENGTH);
			recv_rawpacket(setSocket,newFrame);
			ODRFrame currentFrame = breakFrame(newFrame);

			//Increasing HopCount
			currentFrame.header.hopcount +=1;

			if (currentFrame.header.packetType ==  PACKET_RREQ) {
				handleRREQ(currentFrame,setSocket,ifSockets,numOFInf);

			}
			else if (currentFrame.header.packetType ==  PACKET_RREP) {
				handleRREP(currentFrame,setSocket,ifSockets,numOFInf);
			}

			else if (currentFrame.header.packetType ==  PACKET_MSG)  {
				handleDataPacket(currentFrame, setSocket,ifSockets,numOFInf,udsSocket);
			}
			if(shoudAddRoute(currentFrame)) {

				addRoute(currentFrame.header.sourceAddress,currentFrame.data.source,setSocket,currentFrame.header.hopcount-1,currentFrame.data.forceRoute);
			}
			if (!isObselete(currentFrame.data.source,currentFrame.header.Broadcastid)) {
				if(currentFrame.header.packetType == PACKET_RREQ) {
					addToBroadCastList(currentFrame.data.source,currentFrame.header.Broadcastid);
				}
			}

		}



	}




	// IF UDS SOCKET Find Route and Send Packet

	// IF IF SOCKET
	// 1. IF RREQ  either forward or reply
	// 2. IF RREP  UPDATE ROUTE AND FORWARD TOWARDS SOURCE
	// 3. IF PACKET Find Route and Send Packet


}
