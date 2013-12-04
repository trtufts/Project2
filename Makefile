CC=g++
DEBUG=
CFLAGS=-c -Wall $(DEBUG)
LDFLAGS=-lncursesw $(DEBUG)
SOURCES= display.cpp p_card.cpp p_hand.cpp p_player.cpp p_pot.cpp p_dealer.cpp p_humanPlayer.cpp p_computerPlayer.cpp pokerMain.h ginPlayer.cpp ginHuman.cpp ginComputer.cpp ginCard.cpp ginDeck.cpp ginScoring.cpp ginGame.h GFmain.h Player-1.cpp Deck.cpp RoyalCrown.cpp
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
