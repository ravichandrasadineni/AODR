#include "lib/AddressUtility.h"
#include "lib/GenericUtility.h"
#include "lib/UDSUtility.h"
#define MESSAGE "Hello"

void printMessage() {

}



int main(int argc, char*argv[]) {

	char userchoice[5];
	char ipAddress[INET_ADDRSTRLEN];
	int clientSocket;
	char serverReply[MAXLINE];
	char clientMessage[MAXLINE];
	struct timeval tv;
	int maxfd=0;
	fd_set readSet;
	int isRetransmitted = 0;
	while(1) {
		FD_ZERO (&readSet);
		getUserChoice(userchoice);
		getIpAddressFromDomainName(userchoice,ipAddress);
		clientSocket = getclientBindedsocket();
		connectToODR(clientSocket);
		maxfd = clientSocket + 1;
		while(1) {
			FD_SET(clientSocket,&readSet);
			tv.tv_sec = 2;
			tv.tv_usec = 0;

			if((select(maxfd,&readSet,NULL,NULL,&tv))<0) {
				perror("Select in the client Failed :");
			}
			if(FD_ISSET(clientSocket,&readSet)) {
				msg_recv(clientSocket,serverReply,NULL,NULL);
				printf("SERVER REPLY : %s \n", serverReply);
				break;
			}
		}

		unLinkSocket(clientSocket);
		close(clientSocket);
		isRetransmitted =0;

	}
	return 0;
}
