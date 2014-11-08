#include "lib/AddressUtility.h"
#include "lib/GenericUtility.h"
int main(int argc, char*argv[]) {

	char userchoice[5];
	char ipAddress[INET_ADDRSTRLEN];
	//bindtoTemporary sun_path
	while(1) {
		getUserChoice(userchoice);
		getIpAddressFromDomainName(userchoice,ipAddress);
		printf("%s \n",ipAddress);
	}

	//Unbind

}
