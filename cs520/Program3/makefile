CC=gcc
CFLAGS= -Wall -std=c99
SOURCES=dis_class.c classfile.c utils.c disassemble.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=dis_class
DEBUG_RELEASE=$(EXECUTABLE)_debug

all: $(SOURCES) $(EXECUTABLE) $(DEBUG_RELEASE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(DEBUG_RELEASE): $(OBJECTS) 
	$(CC) -g $(LDFLAGS) $(OBJECTS) -o $@


.c.o:
	$(CC) -g $(CFLAGS) $< -c -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

