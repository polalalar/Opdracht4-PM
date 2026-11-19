# eenvoudige makefile
all: hoofd.o gobord.o
	g++ -Wall -o run gobord.o hoofd.o
gobord.o: gobord.cpp gobord.h
	g++ -Wall -c gobord.cpp
hoofd.o: hoofd.cpp gobord.h
	g++ -Wall -c hoofd.cpp
