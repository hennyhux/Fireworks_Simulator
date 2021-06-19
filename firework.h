/*Author: Henry Zhang*/ 

/*Struct for a single firework*/
struct Firework{
	double launchTime;
	unsigned long int code;
	double fuseTime;
	double X;
	double XV;
	double YV;
	double Y;
	struct Simulation *sim;
};

/*Simulation struct*/
struct Simulation{
	void *p2Head;
  	double dt;
	double ET;
	FILE *ptr2File;

};

/*Struct that contains numbers of structs (de)allocated*/
struct MemoryCount{
	int structsAllocated;
	int structsDeallocated;
};

#define ONETHOUSAND 1000
#define ROUNDCONST 0.01
#define SIXITEMSONLY 6
#define TWOSECONDS 2
#define ONE 1

/*-----Function Declaration-----*/


/*High-Level functions*/
void data(int argc, char *argv[]);
void read(struct Simulation *simPtr, struct MemoryCount *memoryCount, int itemRead, int argc, char *argv[]);
void enterSim(struct Firework *firework, struct MemoryCount *memoryCount);



