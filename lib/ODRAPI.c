/*
 * ODRAPI.c
 *
 *  Created on: Nov 8, 2014
 *      Author: ravichandrasadineni
 */


#include "ODRAPI.h"




char* marshallMessage(char source[INET_ADDRSTRLEN], char destination[INET_ADDRSTRLEN],int port, char* message, int forceRoute) {
	char portStr[6], forceRouteStr[6];
	char *temp = NULL;
	intTochar(port,portStr);
	intTochar(forceRoute,forceRouteStr);
	int messageLength = 2*INET_ADDRSTRLEN + strlen(portStr) + strlen(message) + strlen(forceRouteStr) + 4*strlen(DELIMETER);
	char*  marshelledMessage = (char*)malloc(messageLength*sizeof(char));
	memset(marshelledMessage, '\0', messageLength*sizeof(char));
	strncat(marshelledMessage,source,INET_ADDRSTRLEN);
	strncat(marshelledMessage,DELIMETER, strlen(DELIMETER));
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

void unMarshallMessage(char* source, char* destination,int *port, char* message, char* marshelledMessage, int* forceRoute) {
	char tokenMessage[MAXLINE];
	memset(tokenMessage,'\0',MAXLINE);
	//memset(message,'\0',MAXLINE);
	printf("Marshalled Message in unmarshalling is %s \n",marshelledMessage);
	strncpy(tokenMessage,marshelledMessage,  strlen(marshelledMessage));
	printf("Token Message is %s \n",tokenMessage);
	if(source!=NULL) {
		strncpy(source,strtok(tokenMessage, DELIMETER), INET_ADDRSTRLEN);
		printf("Source is %s \n", source);
	}
	else {
			strtok(tokenMessage, DELIMETER);
		}

	if(destination!=NULL) {
		strncpy(destination,strtok(NULL, DELIMETER), INET_ADDRSTRLEN);
		printf("Destination is %s \n", destination);
	}
	else {
		strtok(NULL, DELIMETER);
	}
	if(port!=NULL) {
		*port = atoi(strtok(NULL, DELIMETER));
		printf("port is %d \n", *port);
	}
	else {
		strtok(NULL, DELIMETER);
	}
	if(forceRoute != NULL) {
		*forceRoute = atoi(strtok(NULL, DELIMETER));
		printf("forceRoute is %d \n", *forceRoute);
	}
	else {
			strtok(NULL, DELIMETER);
		}
	if(message!=NULL) {
		strncpy(message,strtok(NULL, DELIMETER),sizeof(message)-1);
		printf("message is %s \n", message);
	}
}


int msg_send(int sockfd, char source[INET_ADDRSTRLEN], char destination[INET_ADDRSTRLEN],int port, char* message, int forceRoute ){
	char* marshalledMessage = marshallMessage(source, destination,port, message,forceRoute);
	return write(sockfd , marshalledMessage , strlen(marshalledMessage));
}


int msg_recv(int sockfd,  char* message, char source[INET_ADDRSTRLEN],char destination[INET_ADDRSTRLEN], int *port, int* forceRoute){
	char marshelledMessage[MAXLINE];
	memset(marshelledMessage, '\0',MAXLINE);
	int charReturned;
	if((charReturned =read(sockfd , marshelledMessage , MAXLINE )) <0) {
		perror("UnIX DOMAIN SOCKET READ FAILED :");
		exit(0);
	}
	unMarshallMessage(source,destination, port,  message,marshelledMessage, forceRoute);
	return charReturned;
}
