/*Author: Henry Zhang*/ 

#define GRAVITY -32.17405


double calculateDT(double yVelocity);
double updateET(double launchTime, double dt);
double updateXPosition(double xPosition, double xVelocity, double dt);
double updateYPosition(double yPosition, double yVelocity, double dt); 
double updateVerticalVelocity(double yVelocity, double dt);
double updateFuse(double fuseDuration, double dt);
