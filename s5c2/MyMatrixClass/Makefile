
FLAGS:= -O3

all: s5c2


s5c2: Matrix.o s5c2_main.o Makefile
		g++ $(FLAGS) -o s5c2 s5c2_main.o Matrix.o

Matrix.o: Matrix.cpp Matrix.h Makefile
		g++ $(FLAGS) -o Matrix.o -c Matrix.cpp

s5c2_main.o: s5c2_main.cpp Matrix.h Makefile
		g++ $(FLAGS) -o s5c2_main.o -c s5c2_main.cpp


#make run
#run program
run: s5c2
		./s5c2 

#clean files
#make clean
clean:
		rm -f s5c2_main.o Matrix.o


cleanall:
		rm -f s5c2 *.o
