## -*- owcc.mk -*-
##
## User: bernard
## Time: 04 jun. 2016 16:18:31
## Makefile created by Oracle Solaris Studio.
##

CC = owcc
LD = $(CC)

arch = i386
march = -march=$(arch) -mtune=i686
warnings = -Wall -Wextra
optim = -g0 -O2

CFLAGS = $(march) $(warnings) $(optim) $(patsubst -I, -I , $(ipath)) -fwrite-def
LDFLAGS =
