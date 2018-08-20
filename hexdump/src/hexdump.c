/*
 * File:   solhexd.c
 * Author: Bernard TATIN <bernard dot tatin at outlook dot org>
 *
 * Created on 20 février 2016, 23:20
 */

/*
    The MIT License (MIT)

    Copyright (c) 2016 Bernard TATIN <bernard dot tatin at outlook dot org>

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

 */

#include "compat.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "basedef.h"
#include "file-reader.h"
#include "hexops.h"

#define HLEN    16
#define LLEN    256


static uint8_t buffer[HLEN];
static char line[LLEN];

static void dohelp(const int exitCode) {
    fprintf(stdout, "dohelp\n");
    exit(exitCode);
}


static int hexdump(const char* fileName) {
    void *fd = fr_open(fileName, NULL);

    if (fd != NULL) {
        ssize_t read_len;

        while ((read_len = fr_read(fd, buffer, HLEN)) > 0) {
            char *dst = line;
            size_t rest = read_len;
            uint8_t *src = buffer;
            uint8_t *old_src = src;
            int imax = min(HLEN, rest);

            dst += sprintf(dst, "%08lx  ", fr_before_position(fd));
            for (int i = 0; i < imax; i++) {
                dst = put_hex_byte(dst, *(src++));
                if (i == 7) {
                    *(dst++) = ' ';
                }
            }
            if (imax < HLEN) {
                for (int i = imax; i < HLEN; i++) {
                    dst = put3spaces(dst);
                    if (i == 7) {
                        *(dst++) = ' ';
                    }
                }
            }
            src = old_src;
            *(dst++) = ' ';
            *(dst++) = '|';
            for (int i = 0; i < imax; i++) {
                *(dst++) = normalize_byte(*(src++));
            }
            *(dst++) = '|';
            *dst = 0;
            fprintf(stdout, "%s\n", line);
        }
        // BOF : do fprintf BEFORE fr_close, if not, BUG !
        fprintf(stdout, "%08lx\n", fr_before_position(fd));
        fr_close(fd);
    } else {
        fprintf(stderr, "Cannot open file %s\n", fileName);
    }

    return SUCCESS;
}

int main(int argn, char *argv[]) {
    int retCode = SUCCESS;

    for (int i = 1; i < argn; i++) {
        char *arg = argv[i];

        if (strcmp(arg, "--help") == 0) {
            dohelp(SUCCESS);
        } else {
            hexdump(arg);
        }
    }
    return retCode;
}
