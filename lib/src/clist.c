/*
 * File:   clist.c
 * Author: Bernard TATIN <bernard dot tatin at outlook dot org>
 *
 * Created on 10 mars 2016, 22:12
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
#include <stdlib.h>

#include "basedef.h"
#include "clist.h"

TScl_list *cl_list_new(void) {
    TScl_list *list = (TScl_list *)calloc(1, sizeof(TScl_list));
    if (list == NULL) {
        // fprintf(stderr, "Cannot allocate memory !!!\n");
        exit(FAILURE);
    }
    return list;
}

void cl_list_for_each(TScl_list *list, void (*on_element)(TScl_element *elt)) {
    TScl_element *elt = list->first;

    while (elt != NULL) {
        on_element(elt);
        elt = elt->next;
    }
}
