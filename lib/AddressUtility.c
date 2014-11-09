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


 void getIpAddressFromDomainName(char* string, char* ipAddress) {
	struct hostent *he;
	struct in_addr **addr_list;
	int numOfIpaddress =0;
	if(!isValidDomainName(string)) {
		exit(0);
	}
	he = gethostbyname(string);
	printf("Official name is: %s\n", he->h_name);
    addr_list = (struct in_addr **)he->h_addr_list;
    int i;
	char* ip_address = inet_ntoa(*addr_list[0]);
	printf("IP addresses: %s", ip_address);
    	strncpy(ip_address,ipAddress, INET_ADDRSTRLEN);
}
