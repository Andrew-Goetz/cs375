CC = g++
#FLAGS = -03 -f -Wall
OBJECT_FILES = main.o
EXECUTABLE = program1

all:	$(OBJECT_FILES)
		$(CC) $(OBJECT_FILES) -o $(EXECUTABLE)

main.o:	main.cpp
		$(CC) -c main.cpp

clean:
		rm -f *.o $(EXECUTABLE)
