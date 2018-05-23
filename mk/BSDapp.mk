## ======================================================================
## BSD.mk
## Common parts of BSD Makefiles
## Author: Bernard TATIN <bernard dot tatin at outlook dot org>
##
## Created on 20 mai 2018, 07:48
##
## see:
## https://github.com/freebsd/freebsd/blob/master/share/mk/bsd.README
## ======================================================================

##    The MIT License (MIT)
##
##    Copyright (c) 2016 Bernard TATIN <bernard dot tatin at outlook dot org>
##
##    Permission is hereby granted, free of charge, to any person obtaining a copy
##    of this software and associated documentation files (the "Software"), to deal
##    in the Software without restriction, including without limitation the rights
##    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
##    copies of the Software, and to permit persons to whom the Software is
##    furnished to do so, subject to the following conditions:
##
##    The above copyright notice and this permission notice shall be included in all
##    copies or substantial portions of the Software.
##
##    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
##    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
##    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
##    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
##    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
##    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
##    SOFTWARE.

compiler ?= clang
.if ${compiler} == "gcc"
LD = ${compiler}
.endif
CC = ${compiler}
COMPILER_TYPE = ${compiler}

optim ?= -O3 -g0

_os != uname

MACHINE_CPUARCH ?= amd64
CPUTYPE ?= core2

INCDIR += -I/usr/local/include
CFLAGS = $(INCDIR) -D_REENTRANT
COPTS = -std=c11 $(optim) -Wall -pedantic

.if ${MAKE} == "bmake" && ${_os} == "Linux"
NOGCCERROR = 1
.endif

LDFLAGS += -L/usr/local/lib
LDADD += $(LIBS)

PROG = $(MAIN).$(CC).exe
SRCS = $(C_SRC)

MK_OBJDIRS = yes

.include <bsd.prog.mk>

show:
	@echo "CPUTYPE        : ${CPUTYPE}"
	@echo "MACHINE_CPUARCH: ${MACHINE_CPUARCH}"
	@echo "MACHINE_CPU    : ${MACHINE_CPU}"
	@echo "CFLAGS         : ${CFLAGS}"
	@echo "MAKE           : ${MAKE}"

dotest: all
	./${PROG} LICENSE
