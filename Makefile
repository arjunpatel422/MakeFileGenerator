COMPILER=gcc

all: makeFileGenerator

SOURCES=\
main.c\
alloc.c

OBJECTS = $(subst .cpp,.o,$(SOURCES))

makeFileGenerator: $(OBJECTS)
$(COMPILER) -o $@ $(OBJECTS)

command_stream.o Stack.o execute-command.o main.o print-command.o read-command.o : command.h

clean:
rm -fr *.o *~ *.core *.tmp makeFileGenerator