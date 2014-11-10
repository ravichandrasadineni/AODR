/*
 * FrameBufferUtility.h
 *
 *  Created on: Nov 9, 2014
 *      Author: ravichandrasadineni
 */

#ifndef LIB_FRAMEBUFFERUTILITY_H_
#define LIB_FRAMEBUFFERUTILITY_H_

void breakBuffer(char* sourceMac, char* destinationMac, char *data, void* buffer);
void buildBuffer(char* sourceMac, char* destinationMac, char *data, void* buffer);
#endif /* LIB_FRAMEBUFFERUTILITY_H_ */
