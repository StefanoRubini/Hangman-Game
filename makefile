# Make file for Hangman

OBJS	= hangman.o hangmanFunctionsImp.o
CC		= g++
CCFLAGS	= -Wall -Wextra -pedantic -std=c++11 -g

all: hangman

hangman: $(OBJS)
	$(CC) $(CCFLAGS) -o hangman $(OBJS)

hangman.o: hangman.cpp hangmanFunctions.h
	$(CC) $(CCFLAGS) -c hangman.cpp

hangmanFunctionsImp.o: hangmanFunctionsImp.cpp hangmanFunctions.h
	$(CC) $(CCFLAGS) -c hangmanFunctionsImp.cpp

# clean by removing object files.

clean:
	rm $(OBJS) hangman
