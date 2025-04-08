CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp matrix.cpp complex_number.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=program

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)