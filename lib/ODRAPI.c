/*
 * ODRAPI.c
 *
 *  Created on: Nov 8, 2014
 *      Author: ravichandrasadineni
 */


#include "ODRAPI.h"




char* marshallMessage(char destination[INET_ADDRSTRLEN],int port, char* message, int forceRoute) {
	char portStr[6], forceRouteStr[6];
	intTochar(port,portStr);
	intTochar(port,forceRouteStr);
	int messageLength = INET_ADDRSTRLEN + strlen(portStr) + strlen(message) + strlen(forceRouteStr) + 4*strlen("::::");
	char*  marshelledMessage = (char*)malloc(sizeof(messageLength));
	strncpy(marshelledMessage,destination,INET_ADDRSTRLEN);
	strncpy(marshelledMessage, "::::", strlen("::::"));
	strncpy(marshelledMessage,portStr,6);
	strncpy(marshelledMessage, "::::", strlen("::::"));
	strncpy(marshelledMessage,forceRouteStr,strlen(forceRouteStr));
	strncpy(marshelledMessage, "::::", strlen("::::"));
	strncpy(marshelledMessage,destination,INET_ADDRSTRLEN);
	strncpy(marshelledMessage, "::::", strlen("::::"));
	return marshelledMessage;
}

void unMarshallMessage(char* destination,int *port, char* message, char* marshelledMessage) {
	char tokenMessage[strlen(destination)];

	strncpy(marshelledMessage, tokenMessage,  strlen(marshelledMessage));
	if(destination) {
		destination = strtok(tokenMessage, "::::");
	}
	if(port) {
		*port = atoi(strtok(tokenMessage, "::::"));
	}
	if(message) {
		message = strtok(tokenMessage, "::::");
	}
}


int msg_send(int sockfd, char destination[INET_ADDRSTRLEN],int port, char* message, int forceRoute ) {
	char* marshalledMessage = marshallMessage(destination,port, message,forceRoute);
	return write(sockfd , marshalledMessage , strlen(marshalledMessage));
}


int msg_recv(int sockfd,  char* message, char* source, int *port) {
	char marshelledMessage[MAXLINE];
	int charReturned;
	if((charReturned =read(sockfd , marshelledMessage , MAXLINE )) <0) {
		perror("UnIX DOMAIN SOCKET READ FAILED :");
		exit(0);
	}
	unMarshallMessage(source,port,  message,marshelledMessage);
	return charReturned;
}
