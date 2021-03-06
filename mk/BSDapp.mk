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

#.if ${compiler} == "clang"
#CLANG_ANALYZE_OUTPUT ?= html
#CLANG_ANALYZE_OUTPUT_DIR ?= clang-analyze
#.endif

CC = ${compiler}
COMPILER_TYPE = ${compiler}

.ifndef _os
_os != uname
.endif

# .OBJDIR = ./obj
# .if ${_os} == "Linux"
# .OBJDIR != pwd
# # SHAREDSTRINGS ?= 1
# .endif

.ifndef CPUTYPE
CPUTYPE = core2
.endif

INCDIR += -I/usr/local/include
CFLAGS += -pipe $(INCDIR) -D_REENTRANT
CFLAGS += -std=c11

.if ${MAKE} == "bmake" && ${_os} == "Linux"
NOGCCERROR = 1
.endif

LDFLAGS += -L/usr/local/lib
LDADD += $(LIBS)

_cc = ${CC:E}
__cc = ${_cc:C/^\/[^\/]+\///}
PROG = $(MAIN).$(__cc).exe
SRCS = $(C_SRC)


.include <bsd.prog.mk>
# .include <bsd.subdir.mk>

# .if ${_os} != "Linux"
# .include <bsd.clang-analyze.mk>
# .endif

show:
	@echo "MAIN           : ${MAIN}"
	@echo "CC             : ${CC}"
	@echo "__cc           : ${__cc}"
	@echo "PROG           : ${PROG}"
	@echo "CPUTYPE        : ${CPUTYPE}"
	@echo "MACHINE_CPUARCH: ${MACHINE_CPUARCH}"
	@echo "MACHINE_CPU    : ${MACHINE_CPU}"
	@echo "OBJDIR         : ${.OBJDIR}"
	@echo "_here          : ${_here}"
	@echo "MAKE           : ${MAKE}"
	@echo "CFLAGS         : ${CFLAGS}"
# 	@echo "CLANG_ANALYZE_CHECKERS: ${CLANG_ANALYZE_CHECKERS}"
# 	@echo "CLANG_ANALYZE_FLAGS: ${CLANG_ANALYZE_FLAGS}"
# 	@echo "CLANG_ANALYZE_SRCS: ${CLANG_ANALYZE_SRCS}"
# 	@echo "CLANG_ANALYZE_OBJS: ${CLANG_ANALYZE_OBJS}"

dotest: all
	./${PROG} LICENSE
