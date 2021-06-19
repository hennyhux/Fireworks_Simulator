#Author: Henry Zhang

#Default target 
all: lab4

#Lets clean this mess up! Remove all object and zip files
clean:
	rm -rf *.o mkprog *.zip lab4 

#Entry to create the lab executable
lab4: lab4.o memory.o draw.o physics.o bit.o linkedlist.o reliable.o commandArg.o
	gcc -g -o $@ $^ -lncurses -L. -lfire -llinkedlist -lm

#Entry to create the lab executable (unreliable)
lab4u: lab4.o memory.o draw.o physics.o bit.o linkedlist.o unreliable.o commandArg.o
	gcc -g -o $@ $^ -lncurses -L. -lfire -llinkedlist -lm

#Entry to zip all the required files
lab4.zip: makefile *.c *.h *.a reliable.o unreliable.o
	zip $@ makefile *.c *.h *.a reliable.o unreliable.o LAB4_README
	rm -rf install 
	mkdir install
	unzip lab4.zip -d install
	make -C install lab4

#This entry compiles .c files into .o files required for the executable 
%.o: %.c *.h 
	gcc -ansi -pedantic -Wimplicit-function-declaration -Wreturn-type -g -c $< -o $@ -llinkedlist -lncurses -L. -lfire

