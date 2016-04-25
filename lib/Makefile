## -*- Makefile -*-
##
## User: bernard
## Time: 25 avr. 2016 11:41:31
## Makefile created by Oracle Solaris Studio.
##
## This file is generated automatically.
##


#### Compiler and tool definitions shared by all build targets #####
CC = cc
BASICOPTS = -xO3 -xarch=generic64
CFLAGS = $(BASICOPTS) -xCC -Xc -Iinclude


# Define the target directories.
TARGETDIR_libctools=lib64


all: $(TARGETDIR_libctools)/libctools.a

## Target: libctools
OBJS_libctools =  \
	$(TARGETDIR_libctools)/clist.o \
	$(TARGETDIR_libctools)/rbuffer.o


# Link or archive
$(TARGETDIR_libctools)/libctools.a: $(TARGETDIR_libctools) $(OBJS_libctools)
	$(AR) $(ARFLAGS) $@ $(OBJS_libctools)


# Compile source files into .o files
$(TARGETDIR_libctools)/clist.o: $(TARGETDIR_libctools) src/clist.c
	$(COMPILE.c) $(CFLAGS_libctools) $(CPPFLAGS_libctools) -o $@ src/clist.c

$(TARGETDIR_libctools)/rbuffer.o: $(TARGETDIR_libctools) src/rbuffer.c
	$(COMPILE.c) $(CFLAGS_libctools) $(CPPFLAGS_libctools) -o $@ src/rbuffer.c



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_libctools)/libctools.a \
		$(TARGETDIR_libctools)/clist.o \
		$(TARGETDIR_libctools)/rbuffer.o
	rm -f -r $(TARGETDIR_libctools)


# Create the target directory (if needed)
$(TARGETDIR_libctools):
	mkdir -p $(TARGETDIR_libctools)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.Sun-amd64-Solaris

