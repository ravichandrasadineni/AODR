/*
 * ODRAPI.c
 *
 *  Created on: Nov 8, 2014
 *      Author: ravichandrasadineni
 */


#include "ODRAPI.h"
#include "GenericUtility.h"



char* marshallMessage(DataPacket packet) {
	char destPortStr[6], forceRouteStr[6], sourcePortStr[6], RREPSent;
	char *temp = NULL;
	intTochar(packet.destinationPort,destPortStr);
	intTochar(packet.forceRoute,forceRouteStr);
	intTochar(packet.sourcePort,sourcePortStr);
	int messageLength = 2*INET_ADDRSTRLEN + strlen(sourcePortStr) + strlen(destPortStr) + strlen(packet.message) + strlen(forceRouteStr) + 5*strlen(DELIMETER);
	char*  marshelledMessage = (char*)malloc(messageLength*sizeof(char));
	memset(marshelledMessage, '\0', messageLength*sizeof(char));
	strncat(marshelledMessage,packet.source,INET_ADDRSTRLEN);
	strncat(marshelledMessage,DELIMETER, strlen(DELIMETER));
	strncat(marshelledMessage,sourcePortStr,6);
	strncat(marshelledMessage,DELIMETER, strlen(DELIMETER));
	strncat(marshelledMessage,packet.destination,INET_ADDRSTRLEN);
	strncat(marshelledMessage,DELIMETER, strlen(DELIMETER));
	strncat(marshelledMessage,destPortStr,6);
	strncat(marshelledMessage,DELIMETER, strlen(DELIMETER));
	strncat(marshelledMessage,forceRouteStr,strlen(forceRouteStr));
	strncat(marshelledMessage, DELIMETER,strlen(DELIMETER));
	strncat(marshelledMessage,packet.message,strlen(packet.message));
	return marshelledMessage;
}

void unMarshallMessage(char* marshelledMessage, DataPacket *packet) {
	char tokenMessage[MAXLINE];
	memset(tokenMessage,'\0',MAXLINE);
	strncpy(tokenMessage,marshelledMessage,  strlen(marshelledMessage));
	strncpy(packet->source,strtok(tokenMessage, DELIMETER), INET_ADDRSTRLEN);
	packet->sourcePort = atoi(strtok(NULL, DELIMETER));
	strncpy(packet->destination,strtok(NULL, DELIMETER), INET_ADDRSTRLEN);
	packet->destinationPort = atoi(strtok(NULL, DELIMETER));
	packet->forceRoute = atoi(strtok(NULL, DELIMETER));
	strncpy(packet->message,strtok(NULL, DELIMETER),FRAME_BUFFER_LENGTH);

}


int msg_send(int sockfd, DataPacket packet){
	char* marshalledMessage = marshallMessage(packet);
	return write(sockfd , marshalledMessage , strlen(marshalledMessage));
}

int msg_sendTo(int sockfd, DataPacket packet, char fileName[FILE_NAME_LENGTH]){
	char* marshalledMessage = marshallMessage(packet);
	struct sockaddr_un fileSock;
	fileSock.sun_family =  AF_LOCAL;
	strncpy(fileSock.sun_path,fileName, FILE_NAME_LENGTH);
	int returnValue =  sendto(sockfd , marshalledMessage , strlen(marshalledMessage),0,(SA*)&fileSock,sizeof(fileSock));
	return returnValue;
}


int msg_recv(int sockfd,  DataPacket *packet,struct sockaddr_un* cliaddr){
	char marshelledMessage[MAXLINE];
	memset(marshelledMessage, '\0',MAXLINE);
	int charReturned;
	struct sockaddr_un sockAddr;
	memset(&sockAddr, '\0',sizeof(sockAddr));
	int sockAddrLength = sizeof(sockAddr);
	if((charReturned =recvfrom(sockfd , marshelledMessage , MAXLINE,0,(SA*)&sockAddr,&sockAddrLength)) <0) {
		perror("UnIX DOMAIN SOCKET READ FAILED :");
		exit(0);
	}
	unMarshallMessage(marshelledMessage,packet);
	if(cliaddr) {
		*cliaddr = sockAddr;
	}
	return charReturned;
}
