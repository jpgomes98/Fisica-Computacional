
all: s4c6

s4c6: s4c6_main.o s4c6_func.o
	g++ -o s4c6 s4c6_main.o s4c6_func.o

s4c6_main.o: s4c6_main.cpp s4c6_header.h 
	g++ -o s4c6_main.o -c s4c6_main.cpp

s4c6_func.o: s4c6_func.cpp s4c6_header.h
	g++ -o s4c6_func.o -c s4c6_func.cpp

clean:
	rm -f *.o



