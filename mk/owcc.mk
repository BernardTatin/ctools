## -*- owcc.mk -*-
##
## User: bernard
## Time: 04 jun. 2016 16:18:31
## Makefile created by Oracle Solaris Studio.
##

CC = owcc
LD = $(CC)

arch =
warnings = -w=4
optim = -6s -d0

CFLAGS = -std=c11 $(arch) $(warnings) $(optim) $(patsubst -I, i=, $(ipath))
LDFLAGS =


