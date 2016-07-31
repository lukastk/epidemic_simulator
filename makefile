CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lSDL2
IDIR=include
SRCDIR=src
OBJDIR=build
VPATH=
SOURCES= $(SRCDIR)/graphics_main.o $(SRCDIR)/infection_model.cpp $(SRCDIR)/network_constructor.cpp $(SRCDIR)/node.cpp $(SRCDIR)/simulation.cpp $(SRCDIR)/SIR_model.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=sim

graphics: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) -I$(IDIR) $< -o $@ $(LDFLAGS)
