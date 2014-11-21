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
#define ETH_TYPE_LEN 2
#define PACKET_RREQ 0
#define PACKET_RREP 1
#define PACKET_MSG 2
#define MAC_HEADER_LEN 14
#define TIME_SERVER_PORT  1234
#define FILE_NAME_LENGTH 32
#define FRAME_BUFFER_LENGTH 1500
#define FRAME_LENGTH 1514
#define BRODCAST_ID_LENGTH 4
#define HOPCOUNT_LENGTH 2
#define PACKETTYPE_LENGTH 1
#define RREPSENT_LENGTH 1
#define OFF 0
#define ON 0
static const char BRODCAST_MAC[HADDR_LEN] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
extern int CURRENT_BRODCAST_ID;
#endif /* ODRCONSTANTS_H_ */
