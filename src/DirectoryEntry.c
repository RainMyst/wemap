#include <stdio.h>
#include <stdlib.h>
#include "DirectoryEntry.h"

void Direinit(DirectoryEntry **dire)
{
    if ((*dire = malloc(sizeof(DirectoryEntry))) == NULL) {
        fprintf(stderr, "dire malloc error\n");
        exit(1);
    }
    (*dire)->id = 0;
    (*dire)->offset = 0;
}

DirectoryEntry *getDire_ptr()
{
    DirectoryEntry *dire;
    Direinit(&dire);
    return dire;
}

void copyDire(DirectoryEntry *dest, DirectoryEntry *src)
{
    dest->id = src->id;
    dest->offset = src->offset;
}
