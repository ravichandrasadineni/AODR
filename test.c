#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>

#define ETH_FRAME_LEN2 1536

int main (int argc, char*argv) {
	struct sockaddr_ll sADDR;
	int i;
	memset(&sADDR,'\0',sizeof(sADDR));
	int sADDRLength;
	int s = socket(PF_PACKET, SOCK_RAW,htons(ETH_P_ALL));
	if(s == -1) {
		perror("socket Error: ");
		exit(0);
	}
	sADDR.sll_ifindex = 0;
	sADDR.sll_protocol = htons(ETH_P_ALL);
	//	if(bind(s,(struct sockaddr*)&sADDR, sizeof(sADDR))<0) {
	//		perror("bind Error: ");
	//		exit(0);
	//	}
	void* buffer = (void*)malloc(ETH_FRAME_LEN2); /*Buffer for ethernet frame*/
	int length = 0; /*length of the received frame*/
	unsigned char* etherhead = buffer;
	memset(buffer, '\0', ETH_FRAME_LEN2);
	length = recvfrom(s, buffer, ETH_FRAME_LEN2, 0,(struct sockaddr*)&sADDR,sizeof(sADDR));
	if (length <= 0) {
		perror("Error: ");
		exit(0);
	}
	else {
		printf ("MAC address for interface is ");
		for (i=0; i<5; i++) {
			printf ("%02x:", sADDR.sll_addr[i]);
		}
		printf ("%02x\n",((char*) buffer)[5]);
	}

}
