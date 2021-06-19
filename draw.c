/*Author: Henry Zhang*/

#include <stdio.h>
#include <stdlib.h>
#include "firework.h"
#include "libfire.h"
#include "debug.h"
#include "linkedlist.h"
#include "physics.h"
#include "bit.h"
#include "memory.h"
#include "draw.h"


/*You are in text mode, will print out tables and effects according to parameters*/
void textMode(struct Simulation *simPtr, struct Firework *firework, struct MemoryCount *memoryCount)
{

	iterate(simPtr->p2Head, getLowestDT);
	while (some(simPtr->p2Head, listEmpty))
	{
		printTableHeader(simPtr, firework);
		iterate(simPtr->p2Head, printTable);
		iterate(simPtr->p2Head, rangeSafety);
		iterate(simPtr->p2Head, printFireworkExplode);
		checkForDeletion(simPtr, memoryCount, firework);
		iterate(simPtr->p2Head, updateFirework);
		sort(simPtr->p2Head, altitudeSort);
		updateSim(firework);
	}

}

/*You are in graphics mode, will display the appropriate graphics and effects*/
void graphicsMode(struct Simulation *simPtr, struct Firework *firework)
{
	iterate(simPtr->p2Head, getLowestDT);
	while (some(simPtr->p2Head, listEmpty))
	{
		fw_clear();
		iterate(simPtr->p2Head, drawComeUp);
		millisleep((int)(firework->sim->dt * ONETHOUSAND));
		iterate(simPtr->p2Head, drawFireworkExplode);
		deleteSome(&simPtr->p2Head, alreadyExploded, deallocateMemory, 0);
		iterate(simPtr->p2Head, updateFirework);
		updateSim(firework);
	}
	fade(firework);

}


/*Checks if a firework is going to crash and outputs range safety warnings like a boss*/
void rangeSafety(void *data)
{	 
	struct Firework *firework = data;
	double newVY = updateVerticalVelocity(firework->YV, firework->sim->dt);
	if((newVY * firework->YV) < 0 )printf("RANGE SAFETY WARNING: %X is falling at %.1f alt and %.1f downrange with %.3fs till detonation \n", firework->code, updateYPosition(firework->Y, firework->YV, firework->sim->dt),
	updateXPosition(firework->X, firework->XV, firework->sim->dt), firework->fuseTime - firework->sim->dt);

}


/*Checks if anything needs to be nuked, not sure if I took care of all the edge cases*/
void checkForDeletion(struct Simulation *simPtr, struct MemoryCount *memoryCount, struct Firework *firework)
{
	while(some(simPtr->p2Head, alreadyExploded) && updateYPosition(firework->Y, firework->YV, firework->sim->dt) >= 0)
	{
		deleteSome(&simPtr->p2Head, alreadyExploded, deallocateMemory, 1);
		(memoryCount->structsDeallocated)++;	
		printf("DIAGNOSTIC: %d Freed.\n", memoryCount->structsDeallocated);
	}
		
	if(updateYPosition(firework->Y, firework->YV, firework->sim->dt) < 0)
	{
		printImpactSafetyMessage(firework);	
		deleteSome(&simPtr->p2Head, alreadyExploded, deallocateMemory, 1);
		(memoryCount->structsDeallocated)++;	
		printf("DIAGNOSTIC: %d Freed.\n", memoryCount->structsDeallocated);
	}
} 

/*prints out impact safety message*/
void printImpactSafetyMessage(struct Firework *firework)
{
	double newFuse, newX, newY, newTime;
	newFuse = firework->fuseTime - firework->sim->dt;
	newX = updateXPosition(firework->X, firework->XV, firework->sim->dt);
	newY = updateYPosition(firework->Y, firework->YV, firework->sim->dt);
	newTime = firework->sim->ET + firework->sim->dt; 
	printf("RANGE SAFETY WARNING: At %.3f sec %X (made on %i-%i-%i) impacts at (%.2lf, %.2f)' with %.3f seconds remaining\n",
	newTime, firework->code, returnMonth(firework->code), returnDay(firework->code), returnYear(firework->code), newX, newY, newFuse);

}

/*Draws the firework on the come up*/
void drawComeUp(void *data)
{	
	struct Firework *firework = data;
	int sleepTime = (int)firework->sim->dt;
    fw_dot(returnColor(firework->code), firework->X, firework->Y);
	fw_refresh();
}

/*Draws the firework if it explodes*/
void drawFireworkExplode(void *data)
{

	struct Firework *firework = data; 
	long double newDT = 0;
	if (firework->fuseTime <= firework->sim->dt && firework->launchTime <= ((firework->sim->ET) + firework->sim->dt))
	{
		newDT = firework->fuseTime;
		if (returnStarEffect(firework->code))fw_star(returnColor(firework->code), updateXPosition(firework->X,firework->XV, newDT), updateYPosition(firework->Y, firework->YV, newDT));
		if (returnFlashEffect(firework->code))fw_flash();
		if (returnBoomEffect(firework->code))fw_bang();
	}

}

/*Fades the firework*/
void fade(struct Firework *firework)
{

	double loopTime = now() + TWOSECONDS; 
	double currentTime = now();
	while (loopTime - currentTime >= 0)
    	{
      		fw_clear();
      		fw_refresh();
      		millisleep((int)(firework->sim->dt * ONETHOUSAND));
      		currentTime = now(); 
    	}
}

/*Print the header of each output table*/
void printTableHeader(struct Simulation *simPtr, struct Firework *firework)
{
	
	printf("\n"); 
	printf("At ET =  %.3lf (%.15lf) second:\n", firework->sim->ET, firework->sim->ET);
	printf("    Code     (       X,          Y)'  (      VX,        VY) fps       Fuse sec\n");
}

/*Print the actual output table AND updates the variables*/
void printTable(void *data)
{
	struct Firework *aFWPtr = data; 
	if (aFWPtr->launchTime <= aFWPtr->sim->ET)printf("%X at  ( %7.2lf,    %7.2lf)'  ( %7.2lf,   %7.2lf) fps with "
                                                     "%.3lf sec\n", aFWPtr->code, aFWPtr->X , aFWPtr->Y, aFWPtr->XV,
                                                     aFWPtr->YV, aFWPtr->fuseTime);

	if (aFWPtr->launchTime > aFWPtr->sim->ET)printf("%X at  ( %7.2lf,    %7.2lf)'  Holding Until %.3lf\n",
                                                    aFWPtr->code, aFWPtr->X, aFWPtr->Y, aFWPtr->launchTime);
	
	
}

/*Prints the firework explosion effect and free memory*/
void printFireworkExplode(void *data)
{
	struct Firework *firework = data; 
	long double newDT = 0;
	if (firework->fuseTime <= firework->sim->dt && firework->launchTime <= ((firework->sim->ET) + firework->sim->dt))
	{
		/*Check the relation between dt and fuse time*/
		newDT = firework->fuseTime;
		printf("Color #%u starburst at (%.2lf, %.2lf)'\n",
               returnColor(firework->code), updateXPosition(firework->X, firework->XV, newDT), updateXPosition(firework->Y, firework->YV, newDT));

		if (returnFlashEffect(firework->code))printf("Flash at (%.2lf, %.2lf)'\n",
                                                     updateXPosition(firework->X, firework->XV, newDT), updateXPosition(firework->Y, firework->YV, newDT));

  		if (returnBoomEffect(firework->code))printf("Boom at (%.2lf, %.2lf)'\n",
                                                      updateXPosition(firework->X, firework->XV, newDT), updateXPosition(firework->Y, firework->YV, newDT));

	}
}

/*Updates firework*/
void updateFirework(void *data)
{
	struct Firework *firework = data; 
	/*Very ghetto way of rounding*/
	if(firework->launchTime <= (firework->sim->ET + ROUNDCONST) + firework->sim->dt)
	{
		firework->fuseTime = firework->fuseTime - firework->sim->dt;
		firework->X = updateXPosition(firework->X, firework->XV, firework->sim->dt);
		firework->Y = updateYPosition(firework->Y, firework->YV, firework->sim->dt);
		firework->YV = updateVerticalVelocity(firework->YV, firework->sim->dt);
	}
}


/*Updates firework->sim->ET*/
void updateSim(struct Firework *firework)
{
	firework->sim->ET += updateET(firework->launchTime, firework->sim->dt);	

}

/*Gets the lowest dt value for the three fireworks, I realized I can call least on the linked list after I wrote this*/
void getLowestDT(void *data)
{
	struct Firework *firework = data; 
	double dtCompare = calculateDT(firework->YV);
	double dtCurrent = firework->sim->dt;

	if (dtCurrent == 0)firework->sim->dt = dtCompare;
	if (dtCompare < dtCurrent) firework->sim->dt = dtCompare; 

}

/*Check if a firework has exploded already*/
int alreadyExploded(void* data)
{
	struct Firework *firework = data; 	
	return ((firework->fuseTime <= firework->sim->dt && firework->launchTime <= ((firework->sim->ET) + firework->sim->dt)) || updateYPosition(firework->Y, firework->YV, firework->sim->dt) < 0);

}

/*Sort fireworks by altitude*/
int altitudeSort(void *data1, void *data2)
{
	struct Firework *firework1 = data1;
	struct Firework *firework2 = data2; 
	return (firework1->Y > firework2->Y);
}

/*Sort the fireworks by launch time order*/
int launchOrder(void *data1, void *data2)
{
	struct Firework *a = data1, *b = data2;
	return a->launchTime < b->launchTime;

}

/*Checks if a list is empty*/
int listEmpty(void *data)
{
	return ONE;
}

