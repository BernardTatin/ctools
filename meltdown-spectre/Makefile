# ========================================================================
# Makefile for meltdown-spectre.c
# ========================================================================

CC = gcc
CDEFINES = -DCACHE_HIT_THRESHOLD=80
CFLAGS = -Wall -pedantic $(CDEFINES)

LD = gcc
LDFLAGS =

_EXE = meltdown-spectre

EXE = $(_EXE).exe
SOURCES = $(_EXE).c
OBJECTS = $(subst .c,.o,$(SOURCES))

all: $(EXE)

$(EXE): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $(EXE) $(OBJECTS)

%.o: %.c
	@echo "SOURCES : $(SOURCES)"
	@echo "OBJECTS : $(OBJECTS)"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -Rfv $(EXE) $(OBJECTS)

test: all
	./$(EXE)

.PHONY: all clean test

