#include "AddressUtility.h"


int isValidDomainName(char* string) {
	 char stringCopy[strlen(string)];
	 strcpy(stringCopy,string);
	 struct hostent *he;
	 he = gethostbyname(stringCopy);
	 if (he == NULL) {
         herror("Invalid Domain Name :");
         return 0;
    }
	 return 1;
}

void populateLocalAddress(char localAddress[INET_ADDRSTRLEN]) {
	char localHostname[1024];
	gethostname(localHostname, 1023);
	getIpAddressFromDomainName(localHostname,localAddress);
}

void getIpAddressFromDomainName(char* string, char* ipAddress) {
	struct hostent *he;
	struct in_addr localHost;
	struct in_addr **addr_list;
	int numOfIpaddress =0;
	if(!isValidDomainName(string)) {
		exit(0);
	}
	he = gethostbyname(string);
    addr_list = (struct in_addr **)he->h_addr_list;
    int i;
	char* ip_address = inet_ntoa(*addr_list[0]);
    strncpy(ipAddress,ip_address, INET_ADDRSTRLEN);
}
