FLAGS=-g -std=c++11 -pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm
CC=g++

all: item redblacktree main.cpp
	$(CC) $(FLAGS) -c main.cpp
	$(CC) $(FLAGS) -o Dictionary item.o redblacktree.o main.o

item: item.cpp
	$(CC) $(FLAGS) -c item.cpp

redblacktree: redblacktree.cpp
	$(CC) $(FLAGS) -c redblacktree.cpp

clean:
	rm -f *.o
	rm -f *.stackdump
