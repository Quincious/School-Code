CC=gcc
CFLAGS= -Wall -std=c99
SOURCES=dissect_main.c dissect.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=dissect
DEBUG_RELEASE=$(EXECUTABLE)_debug

all: $(SOURCES) $(EXECUTABLE) $(DEBUG_RELEASE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(DEBUG_RELEASE): $(OBJECTS) 
	$(CC) -g $(LDFLAGS) $(OBJECTS) -o $@


.c.o:
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

