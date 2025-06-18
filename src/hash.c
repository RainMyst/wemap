#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "stack.h"
#include "DialEntry.h"

#define HASHSIZE 101
static nlist *hashtab[HASHSIZE];

uint32_t hash(uint32_t id)
{
    uint32_t hashval;
    return (id * 2654435761u) % HASHSIZE;
}

nlist *lookup(uint32_t id)
{
    nlist *np;
    for (np = hashtab[hash(id)]; np != NULL; np = np->next)  
        if (id == np->dial->id)
            return np;
    return NULL;
}

nlist *install(DialEntry *dial)
{
    nlist *np;
    uint32_t hashval;
    if ((np = lookup(dial->id)) == NULL) {
        np = (nlist *) malloc(sizeof(*np));
        if (np == NULL) 
            return NULL;
        np->dial = getDial_ptr();
        copyDial(np->dial, dial);
        hashval = hash(dial->id);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
        push((void *) np->dial);
    } else                                              
        copyDial(np->dial, dial);

    return np;
}

void undef(uint32_t id)
{
    nlist **np, *temp;
    np = &hashtab[hash(id)];  
    if (*np == NULL)                                    //如果第一个是空
        return;

    while (*np) {
        if ((*np)->dial && (*np)->dial->id == id)
            break;
        np = &((*np)->next);
        if (!*np)
            return;
    }
    
    if ((*np)->dial->full[0])
        free((*np)->dial->full[0]);
    if ((*np)->dial->full[1])
        free((*np)->dial->full[1]);
    free((*np)->dial);
    (*np)->dial = NULL;

    temp = *np;
    *np = (*np)->next;
    free(temp);
}

