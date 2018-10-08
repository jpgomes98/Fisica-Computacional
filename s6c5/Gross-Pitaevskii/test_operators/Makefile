FLAG1:= -O3
FLAG2:= -std=c++11

all: teste


teste: Complex.o teste.o Makefile
		g++ $(FLAG1) $(FLAG2) -o teste teste.o Complex.o 

Complex.o: Complex.cpp Complex.h Makefile
		g++ $(FLAG1) $(FLAG2) -o Complex.o -c Complex.cpp

teste.o: teste.cpp Complex.h Makefile
		g++ $(FLAG1) $(FLAG2) -o teste.o -c teste.cpp 


#make run
#run program
run: teste
		./teste 

#clean files
#make clean
clean:
		rm -f *.o


cleanall:
		rm -f teste *.o

cleandats:
		rm -f *.dat
