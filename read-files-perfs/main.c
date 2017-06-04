/*
 * File:   main.c
 * Author: bernard tatin
 *
 * Created on 12 janvier 2017, 12:45
 * From : http://stackoverflow.com/questions/3002122/fastest-file-reading-in-c
 */
/*
 * The MIT License
 *
 * Copyright 2017 bernard tatin.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#include <stdlib.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#if defined(__SUNPRO_C)
#define COMPILER "sun"
#define ALIGNED(x)
#endif
#if defined(__GNUC__) && !defined(__ICC)
#define COMPILER "gcc"
#define ALIGNED(x) __attribute__((aligned(x)))
#endif
#if defined(__ICC)
#define COMPILER "icc"
#define ALIGNED(x) __attribute__((aligned(x)))
#endif

#define ONEK 1024
#define ONEM (ONEK * ONEK)
#define BUFFER_SIZE ONEM
#if !defined(LOOPS)
#define LOOPS 10
#endif
#define ITERATIONS (LOOPS * 1024)

#if defined(__SUNPRO_C)
#pragma align 8 (buffer)
#endif
static unsigned char buffer[BUFFER_SIZE] ALIGNED(4096); // 1 MiB buffer

static const char *output_file = "/dev/null";

static double now() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.;
}

static inline int compute_data(unsigned char *data) {
	int value = 0;
	int fd = open(output_file, O_WRONLY);

	for (int i=0; i<BUFFER_SIZE; i += 1024) {
		value += data[i];
		write(fd, data, 1024);
	}
	close(fd);
	return value;
}

static void test_fread(const char *fileName) {
    FILE *fp = fopen(fileName, "rb");

    for (int i = 0; i < ITERATIONS; ++i) {
        fread(buffer, BUFFER_SIZE, 1, fp);
		compute_data(buffer);
    }
    fclose(fp);
}

static void test_read(const char *fileName) {
    int fd = open(fileName, O_RDONLY);

    for (int i = 0; i < ITERATIONS; ++i) {
        read(fd, buffer, BUFFER_SIZE);
		compute_data(buffer);
    }
    close(fd);
}

static void test_mmap(const char *fileName) {
    unsigned char *mmdata;
    int fd = open(fileName, O_RDONLY);

    for (int i = 0; i < ITERATIONS; ++i) {
        mmdata = mmap(NULL, BUFFER_SIZE, PROT_READ, MAP_PRIVATE, fd, i * BUFFER_SIZE);
        // But if we don't touch it, it won't be read...
        // I happen to know I have 4 KiB pages, YMMV
		compute_data(mmdata);
        munmap(mmdata, BUFFER_SIZE);
    }
    close(fd);
}

static void do_test(void (*fun)(const char *fileName), const char *fileName, const char *testName) {
    double end_time;
    double total_time;
    double start_time = now();

    fun(fileName);

    end_time = now();
    total_time = end_time - start_time;

    printf("-- %-3s %-5s -- ", COMPILER, testName);
    printf("It took %7.6f seconds to read %d GiB. That's %10.2f MiB/s.\n", total_time, LOOPS, ITERATIONS / total_time);
}

int main(int argn, char *argv[]) {
	char *input_file = "/dev/zero";

	if (argn > 1) {
		input_file = argv[1];
	}
    for (int i = 0; i < 10; i++) {
        do_test(test_fread, input_file, "fread");
        do_test(test_read, input_file, "read");
        do_test(test_mmap, input_file, "mmap");
    }
    return 0;
}
