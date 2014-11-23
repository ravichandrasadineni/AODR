/*
 * FilePortMapper.c
 *
 *  Created on: Nov 10, 2014
 *      Author: ravichandrasadineni
 */
#include "FilePortMapper.h"

filePortMap*  filePortMapHead = NULL;
filePortMap*  filePortMapTail = NULL;

int timOutSecs = 0;

void initializeportMap(int timeOut) {
	timOutSecs = timeOut;
	addEntry(TIME_SERVER_PORT, TIME_SERVER);
}

void printPortMapper(){
	filePortMap* startPosition;
	startPosition = filePortMapHead;
	if(startPosition == NULL){
//		printf("FilePortMapper is empty \n");
	}
	else
	{
//		printf("The contents of FilePortMapper is :\nPort\tFileName\t\tSavedTime\n");
		while(startPosition!=NULL){
//			printf("%d %s\t%.24s\r\n",startPosition->port,startPosition->fileName,ctime(&(startPosition->entryTime)));
			startPosition = startPosition->next;
		}
	}
}

int generatePortNumber(char *fileName) {
	//removeTimeOutEntries();
	int isUniquePort =0;
	while(!isUniquePort) {
		int random = rand() % 2000;
//		printf("random port number is %d \n", random);
		if(filePortMapHead == NULL) {
			addEntry(random,fileName);
			return random;
		}
		filePortMap* currentPosition = filePortMapHead;

		while(currentPosition !=NULL) {
			if(!strncmp(fileName,currentPosition->fileName, FILE_NAME_LENGTH)) {
				return currentPosition->port;
			}
			if(currentPosition->port !=random)
				currentPosition=currentPosition->next;
			else {
				break;
			}
		}
		if(currentPosition==NULL)
			addEntry(random,fileName);
		return random;
	}
}



void addEntry(int port, char *fileName) {
	//removeTimeOutEntries();
	if(port <= 0 ) {
		printf("Invalid Port Number \n");
		exit(2);
	}
	if(isEntryExistForPort(port)) {
		deleteEntry(port);
	}

	if(filePortMapHead == NULL) {
		filePortMapHead = (filePortMap*)allocate_void(sizeof(filePortMap));
		filePortMapTail = filePortMapHead;
	}
	else {
		filePortMapTail->next = (filePortMap*)allocate_void(sizeof(filePortMap));
		filePortMapTail = filePortMapTail->next;
	}
	if(port == TIME_SERVER_PORT) {
		filePortMapTail->entryTime =0;
		strncpy(filePortMapTail->fileName,fileName,FILE_NAME_LENGTH);
		filePortMapTail->port= port;
		filePortMapTail->next = NULL;
		return;
	}

	filePortMapTail->entryTime = time(NULL);
	strncpy(filePortMapTail->fileName,fileName,FILE_NAME_LENGTH);
//	printf("FilePortMapper.c : File Path after adding entry is %s \n",filePortMapTail->fileName);
	filePortMapTail->port= port;
	filePortMapTail->next = NULL;
	return ;
}

void deleteEntry(int port) {
	//removeTimeOutEntries();
	if(filePortMapHead == NULL)
		return;
	filePortMap* currentPosition = filePortMapHead;
	filePortMap* prevPosition = NULL;
	while(currentPosition !=NULL) {
		if(currentPosition->port == port) {
			if(prevPosition == NULL) {
				filePortMapHead = filePortMapHead->next;
				if(filePortMapHead  == NULL)
					filePortMapTail = NULL;
				free(currentPosition);
				return;
			}
			else if(currentPosition->next == NULL) {
				filePortMapTail = prevPosition;
				prevPosition->next= NULL;
				free(prevPosition);
			}
			else {
				prevPosition-> next = currentPosition->next;
				free(currentPosition);
				return;
			}
		}
		else {
			prevPosition = currentPosition;
			currentPosition= currentPosition->next;
		}

	}
	return;

}

void removeTimeOutEntries() {
	if(filePortMapHead == NULL)
		return;
	filePortMap* currentPosition = filePortMapHead;
	while(currentPosition !=NULL) {
		if(currentPosition->entryTime == 0) {
			currentPosition= currentPosition->next;
			continue;
		}
		if(difftime(time(NULL),currentPosition->entryTime)>timOutSecs) {
			// order is crucial to avoid dangling pointer
			// move to the next entry and delete the current or current
			// will point to freed memory
			int portToDelete = currentPosition->port;
			currentPosition= currentPosition->next;
			deleteEntry(portToDelete);
		}
		else {
			currentPosition = currentPosition->next;
		}
	}
}

void getFileName(int port, char* fileName) {
	//removeTimeOutEntries();
	if(filePortMapHead == NULL)
		return;
	filePortMap* currentPosition = filePortMapHead;
	while(currentPosition !=NULL) {
		if(currentPosition->port == port) {
			strncpy(fileName,currentPosition->fileName,FILE_NAME_LENGTH);
			return;
		}
		currentPosition = currentPosition->next;
	}
	return;
}

int isEntryExistForPort(int port) {
	//removeTimeOutEntries();
	if(filePortMapHead == NULL)
		return 0;
	filePortMap* currentPosition = filePortMapHead;
	while(currentPosition !=NULL) {
		if(currentPosition->port == port) {
			return 1;
		}
		currentPosition = currentPosition->next;
	}
	return 0;
}

