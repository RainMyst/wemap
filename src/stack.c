#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

#define PTRSIZE sizeof(void *)

static int bufp;
static int maxsize;
static void **buf;

int getbufp()
{
    return bufp;
}

void **stack_to_array()
{
    return buf;
}

void stackinit()
{
    buf = malloc(PTRSIZE * 500);
    if (buf == NULL) {
        fprintf(stderr, "stack malloc error\n");
        exit(2);
    }
    bufp = 0;
    maxsize = 500;
}

void expansion()
{
    int newmaxsize = maxsize * 2;
    void **buf_temp = malloc(newmaxsize * PTRSIZE);
    if (buf_temp == NULL) {
        fprintf(stderr, "stack malloc error\n");
        exit(2);
    }
    memcpy(buf_temp, buf, maxsize * PTRSIZE);
    maxsize = newmaxsize;
    free(buf);
    buf = buf_temp;
}

void *pop()
{
    if (bufp <= 0) {
        fprintf(stderr, "bufp error\n");
        exit(3);
    }
    bufp--;
    return buf[bufp];
}

void push(void *ptr)
{
    if (bufp == maxsize)
        expansion();  
    buf[bufp++] = ptr;
}
