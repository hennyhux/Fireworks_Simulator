/*Author: Henry Zhang*/ 

#include <stdio.h>
#include <stdlib.h>
#include "firework.h"
#include "libfire.h"
#include "debug.h"
#include "linkedlist.h"
#include "physics.h"

/*Calculate the constant dt*/
double calculateDT(double yVelocity)
{ 
	return (0.25 * fw_get_delta_Y()) / yVelocity;	
}

/*Update total elapsed time*/
double updateET(double launchTime, double dt)
{
	return launchTime + dt;
}

/*Update x coordinates*/
double updateXPosition(double xPosition, double xVelocity, double dt)
{

	return xPosition + xVelocity * dt;
}

/*Update y coordinates*/
double updateYPosition(double yPosition, double yVelocity, double dt)
{

	return yPosition + yVelocity * dt + 0.5 * GRAVITY * dt * dt; 

}

/*Update vertical y velocity*/
double updateVerticalVelocity(double yVelocity, double dt)
{

	return yVelocity + GRAVITY * dt;

}



