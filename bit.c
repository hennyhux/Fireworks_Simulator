/*Author: Henry Zhang*/

#include "bit.h"
#include <stdio.h>

/*Applies a bit mask to binary rep of fireworksCode to extract bits*/
int bitShift (unsigned int shiftFactor, int bitFactor, unsigned long int fireworksCode)
{
	int truncatedCode = (int)((unsigned)fireworksCode>>shiftFactor);
	unsigned long int mask = 0;
	int i = 0;
	while (i < bitFactor)
	{
		mask = mask << 1;
		mask = mask | 1;
		i++; 

	}
	return truncatedCode & mask;
}

/*Doesn't take a rocket scientist to figure what this does, returns the month the firework was made*/
int returnMonth(unsigned long int fireworksCode)
{	
	unsigned int shiftFactor = 12;
	unsigned int bitFactor =  4;
	return bitShift(shiftFactor, bitFactor, fireworksCode);
}

/*Return the day the fireworks was made*/
int returnDay(unsigned long int fireworksCode)
{

	unsigned int shiftFactor = 16;
	unsigned int bitFactor =  8;
	return bitShift(shiftFactor, bitFactor, fireworksCode);
}

/*Returns the year the fireworks was made*/
int returnYear(unsigned long int fireworksCode)
{
	unsigned int shiftFactor = 0;
	unsigned int bitFactor =  12;
	return bitShift(shiftFactor, bitFactor, fireworksCode);
}

/*Returns the color of the firework*/
int returnColor(unsigned long int fireworksCode)
{
  	unsigned int shiftFactor = 24;
  	unsigned int bitFactor = 4; 
  	return bitShift(shiftFactor, bitFactor, fireworksCode);

}

/*Return the star effect if bit is equal to 1*/
int returnStarEffect(unsigned long int fireworksCode)
{
  	unsigned int shiftFactor = 31;
  	unsigned int bitFactor = 1;
  	return bitShift(shiftFactor, bitFactor, fireworksCode);

}

/*Determines if the firework has any flash effects*/
int returnFlashEffect(unsigned long int fireworksCode)
{
  	unsigned int shiftFactor = 30;
  	unsigned int bitFactor = 1;
 	return bitShift(shiftFactor, bitFactor, fireworksCode);

}

/*firework boom effect?*/
int returnBoomEffect(unsigned long int fireworksCode)
{
  	unsigned int shiftFactor = 29;
	unsigned int bitFactor = 1;
	return bitShift(shiftFactor, bitFactor, fireworksCode);
}


