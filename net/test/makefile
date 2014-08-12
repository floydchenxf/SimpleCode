all: net

net: main.o log.o
	g++ main.o log.o  -o net

main.o: main.cpp compact.h
	g++ -c main.cpp

log.o: log.cpp log.h compact.h
	g++ -c log.cpp

clean:
	rm -rf *.o net 
