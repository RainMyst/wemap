#ifndef DIRECTORYENTRY_H
#define DIRECTORYENTRY_H
#include <stdint.h>

typedef struct DirectoryEntry {
    uint32_t id;
    uint32_t offset;
}DirectoryEntry;
DirectoryEntry *getDire_ptr();
void copyDire(DirectoryEntry *dest, DirectoryEntry *src);
#endif //!DIRECTORYENTRY_H
