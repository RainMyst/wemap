#ifndef DIRE_HASH_H
#define DIRE_HASH_H
#include <stdint.h>

struct DirectoryEntry;
typedef struct DirectoryEntry DirectoryEntry;
struct direnlist;
typedef struct direnlist direnlist;

struct direnlist {
    direnlist *next;
    DirectoryEntry *dire;
};

uint32_t dire_hash(uint32_t id);
direnlist *dire_lookup(uint32_t id);
direnlist *dire_install(DirectoryEntry *dire);
void dire_undef(uint32_t id);
#endif //!DIRE_HASH_H
