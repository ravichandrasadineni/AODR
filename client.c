#include "lib/AddressUtility.h"
#include "lib/GenericUtility.h"
#include "lib/UDSUtility.h"
int main(int argc, char*argv[]) {

	char userchoice[5];
	char ipAddress[INET_ADDRSTRLEN];
	int clientSocket;

	while(1) {

		getUserChoice(userchoice);
		getIpAddressFromDomainName(userchoice,ipAddress);
		getclientBindedsocket();
		connectToODR(clientSocket);
		printf("connected to ODR\n");
		unLinkSocket(clientSocket);
		close(clientSocket);

	}
	return 0;
}
