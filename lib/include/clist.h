/*
 * File:   clist.h
 * Author: Bernard TATIN <bernard dot tatin at outlook dot org>
 *
 * Created on 10 mars 2016, 21:57
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


#ifndef CLIST_H
#define	CLIST_H

typedef struct _TScl_element {
        void *value;

        struct _TScl_element *next;
} TScl_element;

static INLINE TScl_element *cl_elt_new(void *value) {
        TScl_element *elt = (TScl_element *)calloc(1, sizeof(TScl_element));
        if (elt == NULL) {
        // fprintf(stderr, "Cannot allocate memory !!!\n");
        exit(FAILURE);
        }
        elt->value = value;
        elt->next = NULL;
        return elt;
}

typedef struct _TScl_list {
        TScl_element *first;
} TScl_list;

TScl_list *cl_list_new(void);
void cl_list_for_each(TScl_list *list, void (*on_element)(TScl_element *elt));

static INLINE void cl_list_add(TScl_list *list, TScl_element *elt) {
        if (list->first != NULL) {
                elt->next = list->first;
        }
        list->first = elt;
}

#endif	/* CLIST_H */

