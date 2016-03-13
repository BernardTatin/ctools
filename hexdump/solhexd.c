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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "include/basedef.h"
#include "file-reader.h"

#define HLEN	16
#define LLEN	256

typedef struct {
    char *fileName;
} TSfileConfig;

static uint8_t buffer[HLEN];
static char line[LLEN];

static _Noreturn void dohelp(const int exitCode) {
    fprintf(stdout, "dohelp\n");
    exit(exitCode);
}

static TSfileConfig *duplicate(TSfileConfig *fileConfig) {
    TSfileConfig *fc = (TSfileConfig *) malloc(sizeof (TSfileConfig));

    if (fc == NULL) {
        fprintf(stdout, "ERROR: cannot allocate memory\n");
        exit(FAILURE);
    }
    fc->fileName = fileConfig->fileName;

    fileConfig->fileName = NULL;

    return fc;
}

static int hexdump(TSfileConfig *fc) {
    void *fd = fr_open(fc->fileName, NULL);
    fprintf(stdout, "File : %s\n", fc->fileName);
    if (fd != NULL) {
        ssize_t addr = 0;
        ssize_t read_len;

        while ((read_len = fr_read(fd, buffer, HLEN)) > 0) {
            char *dst = line;
            int rest = read_len;
            uint8_t *src = buffer;

            int wbytes = sprintf(dst, "%08lx: ", addr);
            uint8_t *old_src = src;
            int imax = min(HLEN, rest);

            dst += wbytes;
            for (int i = 0; i < imax; i++) {
                wbytes = sprintf(dst, "%02x ", *(src++));
                dst += wbytes;
            }
            if (imax < HLEN) {
                for (int i = imax; i < HLEN; i++) {
                    wbytes = sprintf(dst, "   ", *(src++));
                    dst += wbytes;
                }
            }
            src = old_src;
            *(dst++) = '\'';
            for (int i = 0; i < imax; i++) {
                uint8_t b = *(src++);
                if (b < 32 || b >= 127) {
                    *(dst++) = '.';
                } else {
                    *(dst++) = (char) b;
                }
            }
            *(dst++) = '\'';
            *dst = 0;
            dst = line;
            addr += HLEN;
            fprintf(stdout, "%s\n", line);
        }
        fr_close(fd);
    } else {
        fprintf(stderr, "Cannot open file %s\n", fc->fileName);
    }

    free(fc);
    return SUCCESS;
}

int main(int argn, char *argv[]) {
    int retCode = SUCCESS;
    TSfileConfig fileConfig = {
        NULL
    };

    for (int i = 1; i < argn; i++) {
        char *arg = argv[i];

        fprintf(stdout, "arg -> %s\n", arg);

        if (strcmp(arg, "--help") == 0) {
            dohelp(SUCCESS);
        } else {
            fileConfig.fileName = arg;
            hexdump(duplicate(&fileConfig));
        }
    }
    return retCode;
}
