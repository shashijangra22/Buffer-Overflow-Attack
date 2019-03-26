//This program has a buffer overflow vulnerability
//The task is to exploit this vulnerability
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int bof(char *str)
{
	char buffer[12];
	strcpy(buffer,str);
	return 1;
}
int main(int argc, char **argv)
{
	char str[517];
	FILE * malfile;
	malfile = fopen("malfile", "r");
	fread(str, sizeof(char), 517, malfile); bof(str);
	printf("Returned Properly\n");
	return 1;
}