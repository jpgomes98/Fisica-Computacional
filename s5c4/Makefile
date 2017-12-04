
FLAGS:= -O3

all: s5c4


s5c4: Matrix.o s5c4_main.o Makefile
		g++ $(FLAGS) -o s5c4 s5c4_main.o Matrix.o

Matrix.o: Matrix.cpp Matrix.h Makefile
		g++ $(FLAGS) -o Matrix.o -c Matrix.cpp

s5c4_main.o: s5c4_main.cpp Matrix.h Makefile
		g++ $(FLAGS) -o s5c4_main.o -c s5c4_main.cpp


#make run
#run program
run: s5c4
		./s5c4 

#clean files
#make clean
clean:
		rm -f s5c4_main.o Matrix.o


cleanall:
		rm -f s5c4 *.o
