
#include "lib/ODRsocketUtility.h"
#include "lib/ODRUtility.h"

int main(int argc,char *arg[]){
	int *ifSockets, numOFInf, udsSocket;
	createAndBindSocketsTOInterfaces(&ifSockets,&numOFInf);
	udsSocket = createAndBindUDS();
	printf("udsSocket is %d \n", udsSocket);
	// Listen on all the sockets
	fd_set readSet;
	int maxfd;
	while(1) {
		getListeningSet(&readSet,&maxfd,ifSockets,numOFInf,udsSocket);
		if((select(maxfd,&readSet,NULL,NULL,NULL))<0) {
			perror("Select on ODR FAILED");
		}

	}




	// IF UDS SOCKET Find Route and Send Packet

	// IF IF SOCKET
	// 1. IF RREQ  either forward or reply
	// 2. IF RREP  UPDATE ROUTE AND FORWARD TOWARDS SOURCE
	// 3. IF PACKET Find Route and Send Packet


}
