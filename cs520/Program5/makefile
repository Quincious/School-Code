CC=gcc
CFLAGS= -Wall -std=c99 -lm 
LDFLAGS= -lpthread
SOURCES=spellcheck.c 
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=spellcheck
DEBUG_RELEASE=$(EXECUTABLE)_debug

all: $(SOURCES) $(EXECUTABLE) $(DEBUG_RELEASE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS) 

$(DEBUG_RELEASE): $(OBJECTS) 
	$(CC) -g $(OBJECTS) -o $@ $(LDFLAGS) 


.c.o:
	$(CC) -g $(CFLAGS) $< -c -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

