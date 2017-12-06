
FLAGS:= -O3

all: s5c5


s5c5: Matrix.o s5c5_main.o Makefile
		g++ $(FLAGS) -o s5c5 s5c5_main.o Matrix.o

Matrix.o: Matrix.cpp Matrix.h Makefile
		g++ $(FLAGS) -o Matrix.o -c Matrix.cpp

s5c5_main.o: s5c5_main.cpp Matrix.h Makefile
		g++ $(FLAGS) -o s5c5_main.o -c s5c5_main.cpp


#make run
#run program
run: s5c5
		./s5c5 

#clean files
#make clean
clean:
		rm -f s5c5_main.o Matrix.o


cleanall:
		rm -f s5c5 *.o
