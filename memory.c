/*Author: Henry Zhang*/

#include <stdio.h>
#include <stdlib.h>
#include "firework.h"
#include "libfire.h"
#include "debug.h"
#include "linkedlist.h"
#include "memory.h"
#include "draw.h"
#include "altmem.h"

/*Lets allocate some dynamic memory, returns address of memory location*/
void *allocateMemory(struct Firework *firework, struct MemoryCount *memoryCount)
{
	struct MemoryCount *memoryCountPtr = memoryCount;
	struct Firework *copyFireworkPtr;
	copyFireworkPtr = (struct Firework *)alternative_malloc(sizeof(struct Firework));
	if (copyFireworkPtr != NULL)
	{
		if(TEXT)printf("DIAGNOSTIC: Allocating space for code %X. ", firework->code);
		(memoryCountPtr->structsAllocated)++;
		if(TEXT)printf("%d Allocated\n" , memoryCountPtr->structsAllocated);

	}
	if (copyFireworkPtr == NULL)printf("ERROR: memory.c: allocateMemory: Something done goofed! malloc() failed!\n");
	return copyFireworkPtr;

}

/*Deallocate memory, hopefully it doesnt blow up*/
void deallocateMemory(void *data)
{
	struct Firework *firework = data;
	if(TEXT)printf("DIAGNOSTIC: Freeing firework code %X. ", firework->code);
	alternative_free(firework);

}

/*Clone Firework structs and add them into a linked list*/
void cloneToList(struct Firework *dtptr, struct Simulation *simPtr, struct Firework firework)
{
	int insertSucessful = 0;
	*dtptr = firework;	
	if(TEXT)insertSucessful = insert(&simPtr->p2Head, dtptr, launchOrder, 1);
	if(GRAPHICS)insertSucessful = insert(&simPtr->p2Head, dtptr, launchOrder, 0);
	if (!insertSucessful)
	{
		printf("ERROR: lab3.c: cloneToList: Failed to insert firework! Freeing firework now \n");
		alternative_free(dtptr);
	}
}








