#include <stdio.h>
#include <stdlib.h>
#include "commandArg.h"


/*Checks to make sure the file isn't missing*/
int checkFilePresent(int argc, char *argv[])
{
	int valid = 1;
	FILE *ptr2File;
	ptr2File = fopen(argv[1], "r");

	if (ptr2File)
	{
		printf("DIAGNOSTIC: Successfully opened %s for input\n", argv[1]);
  		fclose(ptr2File);
	}

	else
	{
		printf("ERROR: %s missing or unable to be accessed!\n", argv[1]);
		valid = 0;
   
	}
	
	return valid;

}

/*Checks that there arent too few arguments*/
int checkArguments(int argc, char *argv[])
{

	int valid = 1;
	if (argc < 2)
	{
		printf("ERROR: %s has too few arguments!\n", argv[0]);
		valid = 0;
	}
	
	return valid;
	
}

/*Closes the input file*/
void closeFile(FILE *ptr2File, char *argv[])
{
	fclose(ptr2File);
	printf("DIAGNOSTIC: %s has been closed\n", argv[1]);

}

