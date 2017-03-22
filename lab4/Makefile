CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
OBJECTS = pqueue.o union_find.o mainestrella.o edge.o vertex.o graph.o helpers.o
N?=0
VALGRINDFLAGS = --leak-check=full --show-reachable=yes
NEATOFLAGS = neato -Tpng -o output.png

kruskal : $(OBJECTS)
		$(CC) $(CFLAGS) -o kruskal $(OBJECTS)

.PHONY : clean
clean :
		rm -f kruskal $(OBJECTS)

valgrind : 
		make clean; make; valgrind $(VALGRINDFLAGS) ./kruskal < input/test$(N).dot

neato :
		$(NEATOFLAGS) input/test$(N).dot

exe :
		make clean; make; ./kruskal < input/test$(N).dot