/*Author: Henry Zhang*/

#include <stdio.h>
#include <stdlib.h>
#include "firework.h"
#include "libfire.h"
#include "debug.h"
#include "linkedlist.h"
#include "memory.h"
#include "draw.h"
#include "commandArg.h"

/*Main function*/
int main(int argc, char *argv[])
{
	/*Get the time at the start of the program*/
	double timeStart = now();


	if (checkArguments(argc, argv) && checkFilePresent(argc, argv))	
	{
		/*Initialize*/
		if ((TEXT || (GRAPHICS && fw_initialize())))
		{
			/*Run Data to began processing*/
			data(argc, argv);	
			if(GRAPHICS)fw_teardown();
		}

		else printf("Graphics failed to initialize, exiting now\n runTime: %f", now() - timeStart);

	}

	printf("Total runtime is %.9lf seconds\n" , now() - timeStart);

	return EXIT_SUCCESS;
}

/*High level details, owns the sim loop, initialize as many structs as needed*/
void data(int argc, char *argv[])
{
	/*Simulation structure for data()*/
	struct Simulation sim = {NULL, 0, 0, NULL};
	struct MemoryCount memoryCount= {0, 0}; 
	int itemRead = 0;
	read(&sim, &memoryCount, itemRead, argc, argv);
}


/*Each fireworks read gets copied into list*/
void read(struct Simulation *simPtr, struct MemoryCount *memoryCount, int itemRead, int argc, char *argv[])
{

	/*read() owns a bunch of local variables, one of which is a Firework struct + derivatives*/
	struct Firework firework, fireworkCopy, *fireworkPtr = &firework, *fireworkPtrCopy = &fireworkCopy, *dtptr;
	struct MemoryCount *memoryCountPtr = memoryCount; 
		
	/*set the struct Simulation pointer inside of Firework struct to point at simulation struct*/
	fireworkPtr->sim = simPtr; fireworkPtr->sim->ptr2File = fopen(argv[1], "r");
	itemRead = fscanf(fireworkPtr->sim->ptr2File, "%lf %X %lf %lf %lf %lf \n", &fireworkPtr->launchTime, &fireworkPtr->code, &fireworkPtr->fuseTime, &fireworkPtr->X, &fireworkPtr->XV, &fireworkPtr->YV);

	/*Scanf loop to read in values into local Firework struct*/
	while (itemRead != -1 && itemRead  == SIXITEMSONLY)
	{
		/*Dynamically allocate space for firework*/
		dtptr = (struct Firework *)allocateMemory(fireworkPtr, memoryCountPtr);

		/*Hands off the address of Firework struct and sim pointer to be added to the linked list*/
		if (dtptr != NULL)cloneToList(dtptr, simPtr, firework);

		/*Next iteration*/
		itemRead = fscanf(fireworkPtr->sim->ptr2File, "%lf %X %lf %lf %lf %lf \n", &fireworkPtr->launchTime, &fireworkPtr->code, &fireworkPtr->fuseTime, &fireworkPtr->X, &fireworkPtr->XV, &fireworkPtr->YV); 
	}
	
	if (some(simPtr->p2Head, listEmpty))enterSim(dtptr, memoryCount);

	if(GRAPHICS || TEXT)closeFile(fireworkPtr->sim->ptr2File, argv);
	printf("\nDone reading, scanf returned %d \n", itemRead);
}


/*Determines how to simulate the fireworks based on debug.h*/
void enterSim(struct Firework *firework, struct MemoryCount *memoryCount)
{
	/*First parameter not needed*/
	if (TEXT)textMode(firework->sim, firework, memoryCount);
		
	if (GRAPHICS)graphicsMode(firework->sim, firework);

}



