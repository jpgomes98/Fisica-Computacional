FLAGS:= -O3

all: s6c2


s6c2: Complex.o s6c2.o Makefile
		g++ $(FLAGS) -o s6c2 s6c2.o Complex.o -fopenmp

Complex.o: Complex.cpp Complex.h Makefile
		g++ $(FLAGS) -o Complex.o -c Complex.cpp

s6c2.o: s6c2.cpp Complex.h Makefile
		g++ $(FLAGS) -o s6c2.o -c s6c2.cpp -fopenmp


#make run
#run program
run: s6c2
		./s6c2 

#clean files
#make clean
clean:
		rm -f *.o


cleanall:
		rm -f s6c2 *.o

cleandats:
		rm -f *.dat
