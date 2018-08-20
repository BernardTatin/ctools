## -*- gcc.mk -*-
##
## User: bernard
## Time: 04 jun. 2016 16:18:31
## Makefile created by Oracle Solaris Studio.
##

CC = gcc
LD = $(CC)

arch = -m64
warns = -Wall -pedantic -Wextra
optim = -O2

CFLAGS = -std=c11 $(arch) $(optim) $(ipath) -errtags=yes -D_REENTRANT $(warns)
LDFLAGS = $(arch)

