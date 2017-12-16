
FLAGS:= -O3

all: schrodinger


schrodinger: Matrix.o s5c6_main.o Makefile
		g++ $(FLAGS) -o schrodinger s5c6_main.o Matrix.o -fopenmp

Matrix.o: Matrix.cpp Matrix.h Makefile
		g++ $(FLAGS) -o Matrix.o -c Matrix.cpp

s5c6_main.o: s5c6_main.cpp Matrix.h Makefile
		g++ $(FLAGS) -o s5c6_main.o -c s5c6_main.cpp -fopenmp


#make run
#run program
run: s5c6
		./s5c6 

#clean files
#make clean
clean:
		rm -f s5c6_main.o Matrix.o


cleanall:
		rm -f schrodinger *.o

cleandats:
		rm -f schrodinger_*.dat
