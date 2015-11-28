PROG = test
CC = g++
FLAGS = -std=c++11 -lblkid
OBJ = Reader.o Function.o main.o

$(PROG) : $(OBJ)
	$(CC) $(FLAGS) -o $(PROG) $(OBJ)

main.o:
	$(CC) $(FLAGS) -c main.cpp

Reader.o: Reader.h
	$(CC) $(FLAGS) -c Reader.cpp

Function.o: Function.h
	$(CC) $(FLAGS) -c Function.cpp

clean:
	rm -rf *.o test
