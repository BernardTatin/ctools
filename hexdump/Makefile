##
## File:   Makefile
## Author: Bernard TATIN <bernard dot tatin at outlook dot org>
##
## Created on 20 février 2016, 23:20
##


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


compiler ?= gcc
src = src

lib=../lib

ipath = -I$(lib)/include


MAIN = hexdump
SRC = $(src)/$(MAIN).c \
	$(src)/file-reader.c \
	$(src)/hexops.c \
	$(lib)/src/clist.c \
	$(lib)/src/rbuffer.c

include ../mk/app.mk

test: $(EXE)
	hexdump -Cv $(EXE) > ref.log
	./$(EXE) $(EXE) > t.log
	diff ref.log t.log
