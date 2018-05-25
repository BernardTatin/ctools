## ======================================================================
## compiler.mk
## compiler configuration
## Author: Bernard TATIN <bernard dot tatin at outlook dot org>
##
## Created on 25 mai 2018, 22:14
##
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

## ======================================================================

compiler ?= clang

_compiler = ${compiler:C/.*\///g}

.if ${_compiler} == "gcc" || ${_compiler:Mgcc[0-9]*} != ""
CC = ${compiler}
COMPILER_TYPE = gcc
.endif

.if ${compiler} == clang || ${_compiler:Mclang[0-9]*} != ""
CC = ${compiler}
COMPILER_TYPE = clang
.endif

.include <bsd.compiler.mk>

.if !target(show_compiler)
show_compiler:
	@echo "======================================================================"
	@echo "Compiler variables"
	@echo
.for var in CC LD compiler _compiler CFLAGS LDFLAGS COMPILER_FEATURES COMPILER_TYPE
	@echo "${var}: ${${var}}"
.endfor

.PHONY: show_compiler
.endif
