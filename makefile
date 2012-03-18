CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=binary.cpp ga.cpp generation.cpp individual.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=ga

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@



