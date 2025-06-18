#ifndef DIALENTRY_H
#define DIALENTRY_H
#include <stdint.h>

typedef struct DialEntry {
    uint32_t id;
    char *full[2];
}DialEntry;

DialEntry getDial();
DialEntry *getDial_ptr();
void readDial(DialEntry *dial, int idx, void *stream);
void copyDial(DialEntry *dest, DialEntry *src);
void transition(DialEntry *dial);
#endif //!DIALENTRY_H
