CC = g++
FLAGS = -03 -f -Wall
OBJECT_FILES = main.o PriorityQueue.o
EXECUTABLE = submission

all:	$(OBJECT_FILES)
		$(CC) $(OBJECT_FILES) -o $(EXECUTABLE)

main.o:	main.cpp PriorityQueue.o
		$(CC) -c main.cpp

PriorityQueue.o: PriorityQueue.h PriorityQueue.cpp
		$(CC) -c PriorityQueue.cpp

clean:
		rm -f *.o $(EXECUTABLE)
