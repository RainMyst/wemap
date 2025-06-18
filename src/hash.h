#ifndef HASH_H
#define HASH_H
#include <stdint.h>
struct DialEntry;
typedef struct DialEntry DialEntry;
struct nlist;
typedef struct nlist nlist;

struct nlist {
    nlist *next;
    DialEntry *dial;
};

uint32_t hash(uint32_t id);
nlist *lookup(uint32_t id);
nlist *install(DialEntry *dial);
void undef(uint32_t id);
#endif //!HASH_H
