CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp keccak.cpp md5.cpp sha-256.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=file_integrity

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@