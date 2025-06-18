#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myread.h"
#include "dire_hash.h"
#include "walk_string.h"
#include "DirectoryEntry.h"

#define WALK(fp, offset) fseek((fp), (offset), SEEK_SET)
#define SMARTMALLOC(x, y) do {if (((x) = malloc((y))) == NULL) { fprintf(stderr, "smartread malloc error\n"); exit(1);} } while(0)

typedef struct {
    uint32_t num;
    uint32_t size;
}header;

static header h;
void gather_dire(void *stream)
{
    FILE *fp = stream;
    DirectoryEntry dire;
    uint32_t temp32;

    READ(fp, &temp32, 4);
    h.num = temp32;
    READ(fp, &temp32, 4);
    h.size = temp32;

    for (int i = 0; i < h.num; i++) {
        READ(fp, &temp32, 4);
        dire.id = temp32;
        READ(fp, &temp32, 4);
        dire.offset = temp32;
        dire_install(&dire);
    }
}

void smartread(void *stream, char **outstr)
{
    FILE *fp = stream;
    int size, newsize;
    size = 50;
    SMARTMALLOC(*outstr, size);
    char *w = *outstr;
    int i = 0;
    while (1) {
        READ(fp, w, 1);
        if (*w == '\0')
            break;
        i++;
        if (i == size) {
            newsize = 2 * size;
            char *tempstr;
            SMARTMALLOC(tempstr, newsize);
            memcpy(tempstr, *outstr, size);
            free(*outstr);
            *outstr = tempstr;
            w = *outstr + i - 1;
            size = newsize;
        }
        w++;
    }
}

void getstring(uint32_t id, char **outstr, void *stream)
{
    FILE *fp = stream;
    direnlist *nlist = dire_lookup(id); 
    if (nlist == NULL || nlist->dire == NULL) {
        fprintf(stderr, "getstring NULL error\n");
        exit(1);
    }
    DirectoryEntry *dire = nlist->dire;
    uint32_t walksize = h.num * 8 + 8 + dire->offset;
    WALK(fp, walksize);
    smartread(fp, outstr);
}
