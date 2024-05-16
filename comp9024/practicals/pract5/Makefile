CC      = gcc
CFLAGS  = -Wall -Werror -std=c11

graphAnalyser : graphAnalyser.o Graph.o
	$(CC) $(CFLAGS) -o graphAnalyser graphAnalyser.o Graph.o

graphAnalyser.o : graphAnalyser.c Graph.h
	$(CC) $(CFLAGS) -c graphAnalyser.c

Graph.o : graph.c Graph.h
	$(CC) $(CFLAGS) -c graph.c

clean : 
	rm -f *.o graphAnalyser