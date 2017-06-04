##
## File:   main.mk
## Author: Bernard TATIN <bernard dot tatin at outlook dot org>
##
## Created on 13 mars 2016, 22:10
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


CC = cc
LD = $(CC)
RM = rm -f

arch = -m64
fullarch = -xtarget=generic -xarch=sse2 $(arch) -xvector=simd -erroff=%none
optim =  

odir = objs$(arch)

ipath += include

CFLAGS = -std=c11 $(arch) $(optim) $(ipath) -errtags=yes -D_REENTRANT
LDFLAGS = $(arch) -L../lib/lib64 -lctools

EXE = $(MAIN)$(arch)
OBJS=$(SRC:$(src)/%.c=$(odir)/%.o)

all: $(odir) $(EXE)

$(odir):
	mkdir -p $@

$(EXE): $(OBJS)
	$(LD) -o $(EXE) $(OBJS) $(LDFLAGS) $(LIBS)

$(odir)/%.o: $(src)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	$(RM) $(EXE) $(OBJS)
	$(RM) a.out core
