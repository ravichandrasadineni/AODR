#include "lib/AddressUtility.h"
#include "lib/GenericUtility.h"
#include "lib/UDSUtility.h"
#define MESSAGE "Hello"

void printRecievedMessage(char* destinationVm, char *time) {
	char localHostname[1024];
	gethostname(localHostname, 1023);
	printf("client at node %s: received from %s , %.24s \n", localHostname,destinationVm, time);

}

void printTimeoutMessage(char* destinationVm) {
	time_t	ticks;
	char localHostname[1024];
	gethostname(localHostname, 1023);
	ticks= time(NULL);
	printf("client at node  %s timeout on response from %s \n", localHostname,destinationVm);

}


void printMessageSend(char* userchoice) {
	char localHostname[1024];
	gethostname(localHostname, 1023);
	printf("sending message from %s to %s \n",localHostname,userchoice);
}


int main(int argc, char*argv[]) {
	DataPacket sendingPacket, recievingPacket;
	char userchoice[5];

	int clientSocket;
	struct timeval tv;
	int maxfd=0;
	fd_set readSet;

	int isRetransmitted = 0;
	strncpy(sendingPacket.message,MESSAGE, strlen(MESSAGE));
	populateLocalAddress(sendingPacket.source);
	while(1) {
		FD_ZERO (&readSet);
		getUserChoice(userchoice);
		getIpAddressFromDomainName(userchoice,sendingPacket.destination);
		printf("client.c : server IP Address is %s \n", sendingPacket.destination);
		clientSocket = getclientBindedsocket();
		connectToODR(clientSocket);
		maxfd = clientSocket + 1;
		while(1) {
			FD_SET(clientSocket,&readSet);
			tv.tv_sec = 2;
			tv.tv_usec = 0;
			sendingPacket.destinationPort = TIME_SERVER_PORT;

			msg_send(clientSocket,sendingPacket);
			if((select(maxfd,&readSet,NULL,NULL,&tv))<0) {
				perror("Select in the client Failed :");
			}
			if(FD_ISSET(clientSocket,&readSet)) {
				msg_recv(clientSocket,&recievingPacket,NULL);
				printRecievedMessage(userchoice, recievingPacket.message);
				break;
			}
			else {
				if(isRetransmitted) {
					sendingPacket.forceRoute = 0;
				}
				else {
					isRetransmitted = 1;
					sendingPacket.forceRoute = 1;
				}
				printTimeoutMessage(userchoice);
			}
		}
		isRetransmitted =0;
		unLinkSocket(clientSocket);
		close(clientSocket);

	}
	return 0;
}
