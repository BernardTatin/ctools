## -*- sunc.mk -*-
##
## User: bernard
## Time: 04 jun. 2016 16:18:31
## Makefile created by Oracle Solaris Studio.
##

CC = llc
LD = $(CC)

arch = x86-64
fullarch = -Wall -pedantic
optim = -O=2

CFLAGS = -O=c11 $(arch) $(optim) $(ipath) -D_REENTRANT
LDFLAGS = $(arch) -L../lib/$(compiler)-lib$(arch) -lctools

