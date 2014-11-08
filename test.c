#include <stdio.h>
#include <string.h>

int main (int argc, char*argv) {
	char temp1[5];
	char temp2[5];
	char temp3[15] ="";
	char temp4[5];
	strncpy(temp1,"hi",5);
	strncpy(temp2,"hello",5);
	strncat(temp3,temp1,5);
	strncat(temp3,"::::",5);
	strncat(temp3,temp2,5);
	strncat(temp3,"::::",5);
	strncpy(temp4,temp3,5);
	printf("String is %s",temp3);

}
