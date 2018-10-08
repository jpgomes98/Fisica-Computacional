FLAG1:= -O3
FLAG2:= -std=c++11

all: GrossPitaevskii


GrossPitaevskii: Complex.o GrossPitaevskii.o Makefile
		g++ $(FLAG1) $(FLAG2) -o GrossPitaevskii GrossPitaevskii.o Complex.o 

Complex.o: Complex.cpp Complex.h Makefile
		g++ $(FLAG1) $(FLAG2) -o Complex.o -c Complex.cpp

GrossPitaevskii.o: GrossPitaevskii.cpp Complex.h Makefile
		g++ $(FLAG1) $(FLAG2) -o GrossPitaevskii.o -c GrossPitaevskii.cpp 


#make run
#run program
run: GrossPitaevskii
		./GrossPitaevskii 

#clean files
#make clean
clean:
		rm -f *.o


cleanall:
		rm -f GrossPitaevskii *.o

cleandats:
		rm -f *.dat
