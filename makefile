CFLAGS= -ansi -O2 -DNDEBUG -D_GLIBCXX_DEBUG -Wall -Wno-sign-compare -Wshadow

all: exec
	
exec: main.o SAT.o
	g++ $(CFLAGS) main.o SAT.o -o program -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cc
	g++ $(CFLAGS) -c main.cc

SAT.o: SAT.hh SAT.cc
	g++ $(CFLAGS) -c SAT.cc

clean: 
	rm *.o program


