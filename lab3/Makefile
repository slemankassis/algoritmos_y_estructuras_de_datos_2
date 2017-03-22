CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
OBJECTS = dict_helpers.o helpers.o index.o data.o pair.o list.o bst.o dict.o
VALGRINDFLAGS = valgrind --leak-check=full --show-reachable=yes

dictionary : $(OBJECTS)
		$(CC) $(CFLAGS) -o dictionary $(OBJECTS) main.c

helpers.o : helpers.c helpers.h dict.h list.h data.h index.h
		$(CC) $(CFLAGS) -c helpers.c -o helpers.o

index.o : index.c index.h
		$(CC) $(CFLAGS) -c index.c -o index.o

data.o : data.c data.h
		$(CC) $(CFLAGS) -c data.c -o data.o

pair.o : pair.c pair.h data.h index.h
		$(CC) $(CFLAGS) -c pair.c -o pair.o

list.o : list.c list.h data.h index.h pair.h
		$(CC) $(CFLAGS) -c list.c -o list.o

bst.o : bst.c bst.o list.h pair.h
		$(CC) $(CFLAGS) -c bst.c -o bst.o

dict.o : dict.c dict.h data.h index.h list.h bst.h
		$(CC) $(CFLAGS) -c dict.c -o dict.o

.PHONY : clean
clean : 
		rm -f dictionary $(OBJECTS)

valgrind : 
		$(VALGRINDFLAGS) ./dictionary
