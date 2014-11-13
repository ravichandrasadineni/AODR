#include "lib/AddressUtility.h"
#include "lib/GenericUtility.h"
#include "lib/UDSUtility.h"
#define MESSAGE "Hello"

void printRecievedMessage(char* destinationVm) {
	time_t	ticks;
	char localHostname[1024];
	gethostname(localHostname, 1023);
	ticks= time(NULL);
	printf("client at node %s: received from %s , %.24s \n", localHostname,destinationVm, ctime(&ticks));

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

	char userchoice[5];
	char serverIpAddress[INET_ADDRSTRLEN];
	int clientSocket;
	char serverReply[MAXLINE];
	char clientMessage[MAXLINE];
	char localclientIp[INET_ADDRSTRLEN];
	struct timeval tv;
	int maxfd=0;
	fd_set readSet;
	int forceRoute =0;
	int isRetransmitted = 0;
	strncpy(clientMessage,MESSAGE, strlen(MESSAGE));
	populateLocalAddress(localclientIp);
	while(1) {
		FD_ZERO (&readSet);
		getUserChoice(userchoice);
		getIpAddressFromDomainName(userchoice,serverIpAddress);
		printf("IP Address is %s \n", serverIpAddress);
		clientSocket = getclientBindedsocket();
		//connectToODR(clientSocket);

		connectToTimeClientServer(clientSocket);
		maxfd = clientSocket + 1;
		while(1) {
			FD_SET(clientSocket,&readSet);
			tv.tv_sec = 2;
			tv.tv_usec = 0;
			msg_send(clientSocket,localclientIp,serverIpAddress,TIME_SERVER_PORT,clientMessage,forceRoute);
			if((select(maxfd,&readSet,NULL,NULL,&tv))<0) {
				perror("Select in the client Failed :");
			}
			if(FD_ISSET(clientSocket,&readSet)) {
				msg_recv(clientSocket,serverReply,NULL,NULL,NULL,NULL);
				printRecievedMessage(userchoice);
				break;
			}
			else {
				if(isRetransmitted) {
					forceRoute = 0;
				}
				else {
					isRetransmitted = 1;
					forceRoute = 1;
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
