#
# Makefile designed for use with gcc.
#
# Copyright (C) 2024, Fredrik Jonsson
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <https://www.gnu.org/licenses/>.
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
