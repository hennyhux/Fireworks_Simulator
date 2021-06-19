/*Author: Henry Zhang*/

/*TEXT functions*/
void textMode(struct Simulation *simPtr, struct Firework *firework, struct MemoryCount *memoryCount);
void printTableHeader(struct Simulation *simPtr, struct Firework *firework);
void printTable(void *data);
void printFireworkExplode(void *data);
void printImpactSafetyMessage(struct Firework *firework);

/*GRAPHICS functions*/
void graphicsMode(struct Simulation *simPtr, struct Firework *firework);
void drawComeUp(void *data);
void drawFireworkExplode(void *data);
void fade(struct Firework *firework);

/*Calculations, updates, and linked-list functions*/
void checkForDeletion(struct Simulation *simPtr, struct MemoryCount *memoryCount, struct Firework *firework);
void updateSim(struct Firework *firework); 
void updateFirework(void *data);
void getLowestDT(void *data);
void rangeSafety(void *data); 
int altitudeSort(void *data1, void *data2);
int alreadyExploded(void* data); 
int launchOrder(void *data1, void *data2);
int listEmpty(void *data);
