FLAGS=-g -std=c++11 -pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm -O3
CC=g++

all: rbtree main.cpp
	$(CC) $(FLAGS) -c main.cpp
	$(CC) $(FLAGS) -o Dictionary rbtree.o main.o


rbtree: rbtree.cpp
	$(CC) $(FLAGS) -c rbtree.cpp

clean:
	rm -f *.o
	rm -f *.stackdump
