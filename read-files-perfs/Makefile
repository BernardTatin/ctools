#
# Makfile
#


compiler ?= gcc

os = $(shell uname)
osfull = $(shell uname -a)
now = $(shell date "+%y%m%d-%H%M%S")
perfs_file = $(os)-perfs/$(now).perfs

RM = rm -f


ifeq ($(compiler),gcc)
CC = gcc
LD = gcc
CFLAGS = -O2 -Wall -m64 -std=c11 -MMD -MP
LDFLAGS = -m64
else ifeq ($(compiler),icc)
CC = icc
LD = icc
CFLAGS = -O2 -Wall -m64 -std=c11 -MMD -MP
LDFLAGS = -m64
else ifeq ($(compiler),sun)
CC = cc
LD = cc
CFLAGS = -fast -xipo -xvector=simd -g +w -s -std=c11 -m64
LDFLAGS = -m64
else
endif
ifdef LOOPS
CFLAGS += -DLOOPS=$(LOOPS)
endif

SOURCES = main.c
OBJECTS = $(SOURCES:%.c=%-$(compiler).o)
EXE = read-files-perfs-$(compiler).exe

all: $(EXE)

$(EXE): $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@

%-$(compiler).o: %.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	@echo "OBJECTS = $(OBJECTS)"
	-$(RM) $(OBJECTS) $(EXE)

test-dir:
	mkdir -p $(os)-perfs

test: test-dir
	$(RM) log; \
	for compiler in gcc icc sun; do \
		$(MAKE) LOOPS=2 compiler=$$compiler all; \
		./read-files-perfs-$${compiler}.exe >> log; \
	done; \
	echo "$(osfull)" > $(perfs_file); \
	sort -k 7 log >> $(perfs_file);

.PHONY: all clean test test-dir
