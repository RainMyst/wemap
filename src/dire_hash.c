#include <stdlib.h>
#include <string.h>
#include "dire_hash.h"
#include "DirectoryEntry.h"

#define HASHSIZE 101
static direnlist *hashtab[HASHSIZE];

uint32_t dire_hash(uint32_t id)
{
    uint32_t hashval;
    return (id * 2654435761u) % HASHSIZE;
}

direnlist *dire_lookup(uint32_t id)
{
    direnlist *np;
    for (np = hashtab[dire_hash(id)]; np != NULL; np = np->next)  
        if (id == np->dire->id)
            return np;
    return NULL;
}

direnlist *dire_install(DirectoryEntry *dire)
{
    direnlist *np;
    uint32_t hashval;
    if ((np = dire_lookup(dire->id)) == NULL) {
        np = (direnlist *) malloc(sizeof(*np));
        if (np == NULL) 
            return NULL;
        np->dire = getDire_ptr();
        copyDire(np->dire, dire);
        hashval = dire_hash(dire->id);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else
        copyDire(np->dire, dire);

    return np;
}

void dire_undef(uint32_t id)
{
    direnlist **np, *temp;
    np = &hashtab[dire_hash(id)];  
    if (*np == NULL)                                    //如果第一个是空
        return;
    while (*np) {
        if ((*np)->dire && (*np)->dire->id == id)
            break;
        np = &((*np)->next);
        if (!*np)
            return;
    }

    free((*np)->dire);
    (*np)->dire = NULL;
    temp = *np;
    *np = (*np)->next;
    free(temp);
}

