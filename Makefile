CC = gcc
FLAGS = -Wall -fPIC -g

tinytest.o: tinytest.c
	$(CC) $(FLAGS) $^ -c

clean:
	rm *.o
