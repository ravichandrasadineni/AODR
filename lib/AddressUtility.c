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

void getDomainName(char* ipAddressString, char* domainName) {
	struct hostent *he;
	struct in_addr ipAddress;
	inet_pton(AF_INET, ipAddressString, &ipAddress);
	he = gethostbyaddr(&ipAddress, sizeof(ipAddress), AF_INET);
	if(he == NULL)  {
		printf(" No valid DomainName for the given IpAddress: %s \n",ipAddressString);
		exit(1);
	}
	strncpy(domainName,he->h_name,strlen(he->h_name));
}


 void getIpAddressFromDomainName(char* string, char* ipAddress) {
	struct hostent *he;
	struct in_addr localHost;
	struct in_addr **addr_list;
	int numOfIpaddress =0;
	char localHostname[1024];
	gethostname(localHostname, 1023);
	if(!isValidDomainName(string)) {
		exit(0);
	}
	he = gethostbyname(string);
    addr_list = (struct in_addr **)he->h_addr_list;
    int i;
	char* ip_address = inet_ntoa(*addr_list[0]);
	printf("IP Address is %s \n", ip_address);
    strncpy(ipAddress,ip_address, INET_ADDRSTRLEN);
    printf("sending message from %s to %s \n",localHostname,string);
}
