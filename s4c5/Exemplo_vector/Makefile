
all: Vector


Vector: Vector.o Vector_main.o
		g++ -o Vector Vector_main.o Vector.o

Vector.o: Vector.cpp Vector.h
		g++ -o Vector.o -c Vector.cpp

Vector_main.o: Vector_main.cpp Vector.h
		g++ -o Vector_main.o -c Vector_main.cpp

clean:
		rm -f *.o 

