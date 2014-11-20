
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


int main(int argc,char *argv[]){
	int *ifSockets, numOFInf, udsSocket;
	createAndBindSocketsTOInterfaces(&ifSockets,&numOFInf);
	udsSocket = createAndBindUDS();
	printf("udsSocket is %d \n", udsSocket);
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
			printf("ODR.c:client FIle path is %s \n", cliaddr.sun_path);
			currentDataPacket.sourcePort = generatePortNumber(cliaddr.sun_path);
			printf("ODR.c:currentDataPacket mesage is %s \n", currentDataPacket.message);
			printf("ODR.c: SourcePortNumber and DestinationPortNumber before sending is %d %d\n", currentDataPacket.sourcePort, currentDataPacket.destinationPort);
			sendDataPacket(currentDataPacket,udsSocket,ifSockets,numOFInf);

		}
		else {
			int setSocket = getSetSocket(ifSockets, numOFInf,&readSet);
			char *newFrame = allocate_strmem(FRAME_LENGTH);
			recv_rawpacket(setSocket,newFrame);
			ODRFrame currentFrame = breakFrame(newFrame);

			//Increasing HopCount
			currentFrame.header.hopcount +=1;



			if(currentFrame.header.packetType == PACKET_RREQ) {
				handleRREQ(currentFrame,setSocket,ifSockets,numOFInf);
			}
			//			else if (currentFrame.header.packetType ==  PACKET_RREP) {
			//				handleRREP(currentFrame);
			//			}

			//			else if (currentFrame.header.packetType ==  PACKET_RREP)  {
			//				handleDataPacket(currentFrame);
			//			}
			//Adding Source Route To RoutingTable
			printf("ODR.C: Set socket is %d \n",setSocket);
			addRoute(currentFrame.header.sourceAddress,currentFrame.data.source,setSocket,currentFrame.header.hopcount,currentFrame.data.forceRoute);

		}



	}




	// IF UDS SOCKET Find Route and Send Packet

	// IF IF SOCKET
	// 1. IF RREQ  either forward or reply
	// 2. IF RREP  UPDATE ROUTE AND FORWARD TOWARDS SOURCE
	// 3. IF PACKET Find Route and Send Packet


}
