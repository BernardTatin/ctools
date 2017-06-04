## -*- Makefile -*-
##
## User: bernard
## Time: 25 avr. 2016 11:41:31
## Makefile created by Oracle Solaris Studio.
##


compiler ?= suncc
ipath += -Iinclude

include ../mk/$(compiler).mk

# Define the target directories.
TARGETDIR_libctools=$(compiler)-lib$(arch)


all: $(TARGETDIR_libctools) $(TARGETDIR_libctools)/libctools.a

## Target: libctools
OBJS_libctools =  \
	$(TARGETDIR_libctools)/clist.o \
	$(TARGETDIR_libctools)/rbuffer.o


# Link or archive
$(TARGETDIR_libctools)/libctools.a: $(TARGETDIR_libctools) $(OBJS_libctools)
	$(AR) $(ARFLAGS) $@ $(OBJS_libctools)


# Compile source files into .o files
$(TARGETDIR_libctools)/%.o: src/%.c
	$(CC) -c $< -o $@ $(CFLAGS)


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

