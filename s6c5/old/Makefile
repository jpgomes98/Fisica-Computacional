FLAG1:= -O3
FLAG2:= -std=c++11

all: s6c5


s6c5: Complex.o s6c5.o Makefile
		g++ $(FLAG1) $(FLAG2) -o s6c5 s6c5.o Complex.o -fopenmp

Complex.o: Complex.cpp Complex.h Makefile
		g++ $(FLAG1) $(FLAG2) -o Complex.o -c Complex.cpp

s6c5.o: s6c5.cpp Complex.h Makefile
		g++ $(FLAG1) $(FLAG2) -o s6c5.o -c s6c5.cpp -fopenmp


#make run
#run program
run: s6c5
		./s6c5 

#clean files
#make clean
clean:
		rm -f *.o


cleanall:
		rm -f s6c5 *.o

cleandats:
		rm -f *.dat
