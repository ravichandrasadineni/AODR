/*
 * MemoryAllocator.h
 *
 *  Created on: Nov 9, 2014
 *      Author: ravichandrasadineni
 */

#ifndef LIB_MEMORYALLOCATOR_H_
#define LIB_MEMORYALLOCATOR_H_

char *allocate_strmem (int len);
uint8_t *allocate_ustrmem (int len);
int * allocate_intmem (int len);
void* allocate_void(int len);

#endif /* LIB_MEMORYALLOCATOR_H_ */
