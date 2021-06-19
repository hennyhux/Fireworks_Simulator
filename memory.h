/*Author: Henry Zhang*/

void cloneToList(struct Firework *dtptr, struct Simulation *simPtr, struct Firework firework);
void *allocateMemory(struct Firework *firework, struct MemoryCount *memoryCount);
void deallocateMemory(void *data);
