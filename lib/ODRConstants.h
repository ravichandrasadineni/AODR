/*
 * ODRConstants.h
 *
 *  Created on: Nov 8, 2014
 *      Author: ravichandrasadineni
 */

#ifndef ODRCONSTANTS_H_
#define ODRCONSTANTS_H_

#define TIME_SERVER "/tmp/rsadineni-timeServer"
#define ODR_SERVER "/tmp/rsadineni-odrServer"
#define ODR_CLIENT_PRE "/tmp/file-XXXXXX"
#define	HADDR_LEN 6	/* same as IFHWADDRLEN in <net/if.h> */
#define DELIMETER ":::"
#define DATAPACKET_BUFFER_SIZE 1024
#define ETHERNET0 "eth0"
#define LOOPBACKIF "lo"
#define ETH_TYPE 4581
#define TYPE_SIZE 2
#define PACKET_RREQ 0
#define PACKET_RREP 1
#define PACKET_MSG 2
#define FILE_NAME_LENGTH 32
#define TIME_SERVER_PORT  1234

#endif /* ODRCONSTANTS_H_ */
