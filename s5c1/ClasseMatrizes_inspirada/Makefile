
FLAGS:= -O3

all: s5c1


s5c1: Matrix.o Matrix_main.o Makefile
		g++ $(FLAGS) -o s5c1 Matrix_main.o Matrix.o

Matrix.o: Matrix.cpp Matrix.h Makefile
		g++ $(FLAGS) -o Matrix.o -c Matrix.cpp

Matrix_main.o: Matrix_main.cpp Matrix.h Makefile
		g++ $(FLAGS) -o Matrix_main.o -c Matrix_main.cpp


#make run
#run program
run: s5c1
		./s5c1 

#clean files
#make clean
clean:
		rm -f Matrix_main.o Matrix.o


cleanall:
		rm -f s5c1 *.o
