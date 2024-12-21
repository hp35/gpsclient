#
# Makefile designed for use with gcc.
#
# Copyright (C) 2024 under GPL 3.0, Fredrik Jonsson
#
PROJECT   = gpsclient
CC        = gcc
CCOPTS    = -std=iso9899:1999
# CCOPTS   = -O2 -Wall -ansi -std=iso9899:1999 -pedantic
LNOPTS    = -lm -lgps

SOURCES  = $(PROJECT).c
HEADERS  = $(SOURCES:.c=.h)
OBJECTS  = $(SOURCES:.c=.o)

all: $(PROJECT)

$(PROJECT): $(OBJECTS)
	$(CC) $(CCOPTS) $(OBJECTS) -o $@ $(LNOPTS)

$(OBJECTS): $(SOURCES)
	for src in $(SOURCES); do $(CC) $(CCOPTS) -c $$src $(LNOPTS); done

clean:
	-rm -Rf *~ *.o $(PROJECT)
