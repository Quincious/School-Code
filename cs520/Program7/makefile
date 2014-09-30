CC=gcc
CFLAGS= -Wall -std=gnu99
LDFLAGS= -lpthread
SOURCES=gc_lib.c prog6_circular_main.c 
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=simple
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

