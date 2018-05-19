/*
 * File:   solar-stuff.c
 * Author: Bernard TATIN <bernard dot tatin at outlook dot org>
 *
 * Created on 3 mars 2016, 22:20
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

/*
 * http://www.geeks3d.com/20120102/programming-tutorial-simple-x11-x-window-code-sample-for-linux-and-mac-os-x/
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

#include <time.h>
#include <sys/time.h>

#include <sys/utsname.h>

#include "freebsd/compat.h"

#include "Xconf.h"
#include "Xhelper.h"
#include "solar-infos.h"

#if defined(__APPLE_CC__)
static const char* s1 = "X11 test app under Mac OS X Lion";
#else
static const char* s1 = "X11 test app under Solaris";
#endif
static const char* s2 = "(C)2012 Geeks3D.com";

static int select_fd;

static bool onKeyPress(XEvent *e) {
    static char buf[128] = {0};
    KeySym keysym;
    XLookupString(&e->xkey, buf, sizeof buf, &keysym, NULL);
    return (keysym == XK_Escape);
}

static void onExposeChild(void) {
    TSsysconf *sysconf = soli_sysconf();

    XhDrawString(xconf_main.childStatus, 10, 12, "%02d:%02d:%02d", sysconf->tm->tm_hour, sysconf->tm->tm_min, sysconf->tm->tm_sec);
    //fprintf(stdout, "onExposeChild\n");
}

static void onExposeMainWindow(Display *display, const int screen, const Window win) {
    xconf_init_gc();
    int x_offset = 10;
    int y_offset = 20;
    TSsysconf *sysconf = soli_sysconf();

    XhDrawString(xconf_main.win, x_offset, y_offset, (char *) s1);
    y_offset += 20;
    XhDrawString(xconf_main.win, x_offset, y_offset, (char *) s2);
    y_offset += 20;

    if (sysconf->uname_ok) {
        XhDrawString(xconf_main.win, x_offset, y_offset, "System information -->");
        y_offset += 15;

        XhDrawString(xconf_main.win, x_offset, y_offset, "- System: %s", sysconf->sname.sysname);
        y_offset += 15;

        XhDrawString(xconf_main.win, x_offset, y_offset, "- Release: %s", sysconf->sname.release);
        y_offset += 15;

        XhDrawString(xconf_main.win, x_offset, y_offset, "- Version: %s", sysconf->sname.version);
        y_offset += 15;

        XhDrawString(xconf_main.win, x_offset, y_offset, "- Machine: %s", sysconf->sname.machine);
        y_offset += 20;
    }

    x_offset = 250;
    y_offset = 20;
    XhDrawString(xconf_main.win, x_offset, y_offset, "%ld CPU%s installed, %ld online", sysconf->num_procs,
            (sysconf->num_procs > 1) ? "s" : "", sysconf->procs_online);
    y_offset += 20;
    XhDrawString(xconf_main.win, x_offset, y_offset, "%lld MB physical memory, %lld MB free", sysconf->mem, sysconf->free_mem);
    y_offset += 20;
    XhDrawString(xconf_main.win, x_offset, y_offset, "average load : %9.2f | %9.2f | %9.2f", sysconf->load_av [LOADAVG_1MIN], sysconf->load_av [LOADAVG_5MIN], sysconf->load_av [LOADAVG_15MIN]);
}

static int do_select(void) {
    static struct timeval select_time_val;
    static fd_set select_rfds;

    memset(&select_time_val, 0, sizeof (select_time_val));
    select_time_val.tv_sec = 1;
    select_time_val.tv_usec = 0;
    FD_ZERO(&select_rfds);
    FD_SET(select_fd, &select_rfds);
    return select(select_fd + 1, &select_rfds, NULL, NULL, &select_time_val);
}

static void send_ExposeEvent(void) {
    static XExposeEvent ee;
    memset(&ee, 0, sizeof (XExposeEvent));
    ee.type = Expose;
    ee.display = xconf_main.display;
    ee.window = xconf_main.win;
    ee.width = 660;
    ee.height = 220;
    XSendEvent(xconf_main.display, xconf_main.win, True, ExposureMask, (XEvent *) & ee);

    memset(&ee, 0, sizeof (XExposeEvent));
    ee.type = Expose;
    ee.display = xconf_main.display;
    ee.window = xconf_main.childStatus;
    ee.width = 640;
    ee.height = 20;
    XSendEvent(xconf_main.display, xconf_main.childStatus, True, ExposureMask, (XEvent *) & ee);
}

int main(int argc, char** argv) {
    char buffer[128];
    TSsysconf *sysconf;

    xconf_open(100, 100, 660, 200);
    soli_start();
    sysconf = soli_sysconf();

#if defined(__APPLE_CC__)
    y_offset += 15;
    XStoreName(display, win, "Geeks3D.com - X11 window under Mac OS X (Lion)");
#else
    if (sysconf->uname_ok) {
        sprintf(buffer, "Geeks3D.com - X11 window under Unix (%s)", sysconf->sname.sysname);
    } else {
        strcpy(buffer, "Geeks3D.com - X11 window under Unix");
    }
    XStoreName(xconf_main.display, xconf_main.win, buffer);
#endif
    Atom WM_DELETE_WINDOW = XInternAtom(xconf_main.display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(xconf_main.display, xconf_main.win, &WM_DELETE_WINDOW, 1);

    XEvent e;
    bool end = false;

    select_fd = ConnectionNumber(xconf_main.display);

    XFlush(xconf_main.display);
    while (!end) {
        if (do_select()) {
            while (XPending(xconf_main.display)) {
                XNextEvent(xconf_main.display, &e);
                switch (e.type) {
                    case NoExpose:
                        break;
                    case GraphicsExpose:
                        break;
                    case VisibilityNotify:
                        XClearArea(xconf_main.display, xconf_main.win, 0, 0, 0, 1, True);
                        break;
                    case Expose:
                        if (e.xexpose.count == 0) {
                            if (e.xexpose.window == xconf_main.win) {
                                onExposeMainWindow(xconf_main.display, xconf_main.screen, xconf_main.win);
                            } else {
                                onExposeChild();
                            }
                        }
                        break;
                    case KeyPress:
                        end = onKeyPress(&e);
                        break;
                    case ClientMessage:
                        end = ((unsigned int) (e.xclient.data.l[0]) == WM_DELETE_WINDOW);
                        break;
                }
            }
        } else {
            send_ExposeEvent();
        }
        XFlush(xconf_main.display);
    }
    soli_stop();
    xconf_close();
    return 0;
}
