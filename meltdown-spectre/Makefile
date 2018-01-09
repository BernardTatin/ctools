# ========================================================================
# Makefile for meltdown-spectre.c
# ========================================================================

CC = gcc
CFLAGS = -Wall -pedantic
LD = gcc
LDFLAGS =

_EXE = meltdown-spectre

EXE = $(_EXE).exe
SOURCES = $(_EXE).c
OBJECTS = $(subst .c,.o,$(SOURCES))

all: $(EXE)

$(EXE): $(OBJECTS)
	$(LD) -o $(EXE) $(OBJECTS)

%.o: %.c
	@echo "SOURCES : $(SOURCES)"
	@echo "OBJECTS : $(OBJECTS)"
	$(CC) -c $< -o $@

clean:
	rm -Rfv $(EXE) $(OBJECTS)

test: all
	./$(EXE)

.PHONY: all clean test

