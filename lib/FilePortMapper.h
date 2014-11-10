/*
 * FilePortMapper.h
 *
 *  Created on: Nov 10, 2014
 *      Author: ravichandrasadineni
 */

#ifndef LIB_FILEPORTMAPPER_H_
#define LIB_FILEPORTMAPPER_H_

#include "unp.h"
#include "MemoryAllocator.h"
#include "ODRConstants.h"
#include <time.h>

struct filePortMapper{
	int port;
	char fileName[32];
	time_t entryTime;
	struct filePortMapper *next;
};
typedef struct filePortMapper filePortMap;
void initializeportMap();
void addEntry(int port, char *fileName);
void deleteEntry(int port);
void removeTimeOutEntries();
void getFileName(int port, char* fileName);
int isEntryExistForPort(int port);




#endif /* LIB_FILEPORTMAPPER_H_ */
