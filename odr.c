#include "lib/odr.h"
int main(int argc,char *arg[]){
	int pfPacket;
	pfPacket = socket(PF_PACKET,SOCK_DGRAM,htons(1236));
	if(pfPacket<0){
		perror("creation of socket failed :");
		exit(0);
	}
	struct sockaddr_ll *forread,*check;
	memset(forread,'\0',sizeof(forread));
	check->sll_ifindex = 2;
	check->sll_protocol = htons(1236);
	if(bind(pfPacket,(struct sockaddr *)check,sizeof(check)) < 0){
		perror("Failed to bind the socket :");
		exit(0);
	}
	if(read(pfPacket,&forread,sizeof(forread)) < 0){
		perror("Read failed with error :");
		exit(0);
	}
	printf("Read successfully\n");
	return 1;

}
