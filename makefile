# The compilers to use.
CC = g++

# Compiler options
CFLAGS= -c -m64 -O3 -Wall

# Sources and Common clases sources
SOURCES= main.cpp StringTokenizer.cpp

# Objects
OBJECTS=$(SOURCES:.cpp=.o)

# Name of the executable
EXECUTABLE=mrmr-reader

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

clean:
	rm *.o
	rm mrmr-reader