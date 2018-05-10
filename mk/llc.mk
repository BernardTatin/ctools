## -*- sunc.mk -*-
##
## User: bernard
## Time: 04 jun. 2016 16:18:31
## Makefile created by Oracle Solaris Studio.
##

CC = clang
LD = $(CC)

arch = -m64
fullarch = -Wall -pedantic
optim = -O2

CFLAGS = -std=c11 $(arch) $(optim) $(ipath) -D_REENTRANT
LDFLAGS = $(arch)

