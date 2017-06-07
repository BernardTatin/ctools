## -*- sunc.mk -*-
##
## User: bernard
## Time: 04 jun. 2016 16:18:31
## Makefile created by Oracle Solaris Studio.
##

CC = cc
LD = $(CC)

arch = -m64
fullarch = -xtarget=generic -xarch=sse2 $(arch) -xvector=simd -erroff=%none
optim = -xO2
# optim =

CFLAGS = -std=c11 $(arch) $(optim) $(ipath) -errtags=yes -D_REENTRANT
LDFLAGS = $(arch) -L../lib/$(compiler)-lib$(arch) -lctools
