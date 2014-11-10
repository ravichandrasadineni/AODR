/*
 * ODRAPI.c
 *
 *  Created on: Nov 8, 2014
 *      Author: ravichandrasadineni
 */


#include "ODRAPI.h"




char* marshallMessage(char destination[INET_ADDRSTRLEN],int port, char* message, int forceRoute) {
	char portStr[6], forceRouteStr[6];
	char *temp = NULL;
	intTochar(port,portStr);
	intTochar(forceRoute,forceRouteStr);
	int messageLength = INET_ADDRSTRLEN + strlen(portStr) + strlen(message) + strlen(forceRouteStr) + 4*strlen(DELIMETER);
	char*  marshelledMessage = (char*)malloc(messageLength*sizeof(char));
	memset(marshelledMessage, '\0', messageLength*sizeof(char));
	strncat(marshelledMessage,destination,INET_ADDRSTRLEN);
	strncat(marshelledMessage,DELIMETER, strlen(DELIMETER));
	strncat(marshelledMessage,portStr,6);
	strncat( marshelledMessage,DELIMETER, strlen(DELIMETER));
	strncat(marshelledMessage,forceRouteStr,strlen(forceRouteStr));
	strncat( marshelledMessage, DELIMETER,strlen(DELIMETER));
	strncat(marshelledMessage,message,strlen(message));
	printf("Marshelled message in marshalling is %s \n",marshelledMessage );
	return marshelledMessage;
}

void unMarshallMessage(char* destination,int *port, char* message, char* marshelledMessage) {
	char tokenMessage[MAXLINE];
	memset(tokenMessage,'\0',MAXLINE);
	//memset(message,'\0',MAXLINE);
	printf("Marshalled Message in unmarshalling is %s \n",marshelledMessage);
	strncpy(tokenMessage,marshelledMessage,  strlen(marshelledMessage));
	printf("Token Message is %s \n",tokenMessage);
	if(destination!=NULL) {
		strncpy(destination,strtok(tokenMessage, "::::"), INET_ADDRSTRLEN);
		printf("Destination is %s \n", destination);
	}
	else {
		strtok(tokenMessage, "::::");
	}
	if(port!=NULL) {
		*port = atoi(strtok(NULL, "::::"));
		printf("port is %d \n", *port);
	}
	else {
		strtok(NULL, "::::");
	}
	// to remove fourceRouteBit
	strtok(NULL, "::::");
	if(message!=NULL) {
		strncpy(message,strtok(NULL, "::::"),sizeof(message)-1);
		printf("message is %s \n", message);
	}
}


int msg_send(int sockfd, char destination[INET_ADDRSTRLEN],int port, char* message, int forceRoute ) {
	char* marshalledMessage = marshallMessage(destination,port, message,forceRoute);
	return write(sockfd , marshalledMessage , strlen(marshalledMessage));
}


int msg_recv(int sockfd,  char* message, char* source, int *port) {
	char marshelledMessage[MAXLINE];
	memset(marshelledMessage, '\0',MAXLINE);
	int charReturned;
	if((charReturned =read(sockfd , marshelledMessage , MAXLINE )) <0) {
		perror("UnIX DOMAIN SOCKET READ FAILED :");
		exit(0);
	}
	unMarshallMessage(source,port,  message,marshelledMessage);
	return charReturned;
}
