
FLAGS:= -O3

all: g0p3c3


g0p3c3: Matrix.o g0p3c3.o Makefile
		g++ $(FLAGS) -o g0p3c3 g0p3c3.o Matrix.o

Matrix.o: Matrix.cpp Matrix.h Makefile
		g++ $(FLAGS) -o Matrix.o -c Matrix.cpp

g0p3c3.o: g0p3c3.cpp Matrix.h Makefile
		g++ $(FLAGS) -o g0p3c3.o -c g0p3c3.cpp


#make run
#run program
run: g0p3c3
		./g0p3c3 

#clean files
#make clean
clean:
		rm -f g0p3c3 g0p3c3.o Matrix.o


cleanall:
		rm -f g0p3c3 g0p3c3.o Matrix.o g0p3c3_out*.txt
