/*
 * File:   private-Xhelper.c
 * Author: Bernard TATIN <bernard dot tatin at outlook dot org>
 *
 * Created on 4 mars 2016, 18:46
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

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xresource.h>
#include <X11/keysym.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <sys/utsname.h>

#include "Xconf.h"
#include "Xhelper.h"


TSXconfig xconf_main;
static XSetWindowAttributes attributes;

bool xconf_open(const int x, const int y, const int width, const int height) {
    Visual *visual;
    int depth;

    memset(&attributes, 0, sizeof (XSetWindowAttributes));
    xconf_main.display = XOpenDisplay(NULL);
    if (xconf_main.display == NULL) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }
    xconf_main.screen = DefaultScreen(xconf_main.display);
    attributes.background_pixel = XWhitePixel(xconf_main.display, xconf_main.screen);
    visual = DefaultVisual(xconf_main.display, xconf_main.screen);
    depth = DefaultDepth(xconf_main.display, xconf_main.screen);
    xconf_main.root_window = RootWindow(xconf_main.display, xconf_main.screen);
    xconf_main.win = XCreateWindow(xconf_main.display, xconf_main.root_window, x, y, width, height, 5, depth, InputOutput,
            visual, CWBackPixel, &attributes);

    XSelectInput(xconf_main.display, xconf_main.win, ExposureMask | KeyPressMask | GCGraphicsExposures | SubstructureNotifyMask);
    xconf_main.gr_values.function = GXcopy;
    xconf_main.gr_values.plane_mask = AllPlanes;
    xconf_main.gr_values.foreground = BlackPixel(xconf_main.display, xconf_main.screen);
    xconf_main.gr_values.background = WhitePixel(xconf_main.display, xconf_main.screen);
    xconf_main.gr_context = XCreateGC(xconf_main.display, xconf_main.win,
            GCClipMask | GCFunction | GCPlaneMask | GCForeground | GCBackground | GCGraphicsExposures,
            &xconf_main.gr_values);

    xconf_main.gc = xconf_main.gr_context;
    XMapWindow(xconf_main.display, xconf_main.win);

    xconf_main.childStatus = XCreateWindow(xconf_main.display, xconf_main.win, 10, 170, width - 20, 25, 2, depth, InputOutput,
            visual, CWBackPixel, &attributes);
    // xconf_main.childStatus = XCreateSimpleWindow(xconf_main.display, xconf_main.win, 10, 170, 640, 20, 0, 0,
            // WhitePixel(xconf_main.display, xconf_main.screen));
    XSelectInput(xconf_main.display, xconf_main.childStatus, ExposureMask);
    XMapWindow(xconf_main.display, xconf_main.childStatus);
    return true;
}
