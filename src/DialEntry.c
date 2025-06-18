#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "myread.h"
#include "DialEntry.h"

void transition(DialEntry* dial)
{
    char* w;
    if (dial->full[0])
        for (w = dial->full[0]; *w; w++)
            if (*w == '\"')
                *w = '_';
    if (dial->full[1])
        for (w = dial->full[1]; *w; w++) 
            if (!isgraph(*w) || *w == '\\' || *w == '\"' || *w == '|' || *w == ':' || *w == '*' || *w == '<' || *w == '>' || *w == '/' || *w == '?')
                *w = '_';
            
}

void Dialinit(DialEntry **dial)
{
    if ((*dial = malloc(sizeof(DialEntry))) == NULL) {
        fprintf(stderr, "dial malloc error\n");
        exit(2);
    }
    (*dial)->full[1] = (*dial)->full[0] = NULL;
}

DialEntry *getDial_ptr()
{
    DialEntry *dial;
    Dialinit(&dial);
    return dial;
}

DialEntry getDial()
{
    DialEntry dial;
    dial.full[1] = dial.full[0] = NULL;
    return dial;
}

void copyDial(DialEntry *dest, DialEntry *src)
{
    dest->id = src->id;
    if (dest->full[0] == NULL)
        dest->full[0] = src->full[0];
    if (dest->full[1] == NULL)
        dest->full[1] = src->full[1];
}

void *mallocc(int size)
{
    void *buf = malloc(size);
    if (buf == NULL) {
        fprintf(stderr, "mallocc error\n");
        exit(2);
    }
    return buf;
}

void readDial(DialEntry *dial, int idx, void *stream)
{
    FILE *fp = stream;
    uint32_t visit;

    READ(fp, &visit, 4);
    uint32_t tempsonsize = visit;

    fseek(fp, 4, SEEK_CUR);                      //移位四个
    READ(fp, &visit, 4);
    dial->id = visit;

    fseek(fp, 8, SEEK_CUR);                      //移位八个
    uint32_t atsize = 0;                    
    while (1) {
        if (atsize >= tempsonsize)
            return;
        char name[5] = { 0 };
        READ(fp, name, 4);
        if (strcmp(name, "FULL") == 0)
            break;

        visit = 0;
        READ(fp, &visit, 2);

        fseek(fp, visit, SEEK_CUR);
        atsize += visit + 2 + 4;
    }

    visit = 0;
    READ(fp, &visit, 2);
    char *buf = mallocc(visit);
    READ(fp, buf, visit);

    dial->full[idx] = buf;
}
