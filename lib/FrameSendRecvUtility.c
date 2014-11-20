/*
 * FrameSendRecvUtility.c
 *
 *  Created on: Nov 16, 2014
 *      Author: ravichandrasadineni
 */
#include "FrameSendRecvUtility.h"

void send_rawpacket (int raswSock, unsigned char * frame) {
	int sent= 0;
	int pack_len = FRAME_LENGTH;
	if((sent=write(raswSock, frame, pack_len)) != pack_len)
	{
		if(sent < 0) {
			perror("error while sending packets ");
		}
		printf("Could only send %d bytes of packet of length  %d\n", sent, pack_len);

	}

}

int recv_rawpacket(int rawsock, unsigned char *pkt) {
	int recv= 0;
	int pkt_len = FRAME_LENGTH;
	recv = read(rawsock, pkt, pkt_len);
	if(recv <0) {
		perror("error while receiving packets ");
	}
	return recv;
}


