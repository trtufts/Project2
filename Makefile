# This is an example makefile
# It is very important to add -lncursesw for the ncurses library
CC=g++
DEBUG=
CFLAGS=-c $(DEBUG)
LDFLAGS=-lncursesw $(DEBUG)
SOURCES=display.cpp ginPlayer.cpp ginHuman.cpp ginComputer.cpp ginCard.cpp ginDeck.cpp ginScoring.cpp ginGame.h RoyalCrown.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=RoyalCrown

all: clean $(SOURCES) $(EXECUTABLE)

debug: clean
debug: DEBUG +=-g
debug: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)

