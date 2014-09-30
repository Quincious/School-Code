CC=gcc
CFLAGS= -Wall -std=c99 
LDFLAGS= -lpthread
SOURCES=graphsearch.c graph.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=graphsearch
DEBUG_RELEASE=$(EXECUTABLE)_debug
PROF_RELEASE=$(EXECUTABLE)_prof

all: $(SOURCES) $(EXECUTABLE) $(DEBUG_RELEASE) $(PROF_RELEASE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS) 

$(DEBUG_RELEASE): $(OBJECTS) 
	$(CC) -g $(OBJECTS) -o $@ $(LDFLAGS) 

$(PROF_RELEASE): $(OBJECTS) 
	$(CC) -g -pg $(OBJECTS) -o $@ $(LDFLAGS) 

.c.o:
	$(CC) -g -pg $(CFLAGS) $< -c -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

