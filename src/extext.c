#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *exmallocc(int size)
{
    void *buf = malloc(size);
    if (buf == NULL) {
        fprintf(stderr, "mallocc in extext error\n");
        exit(1);
    }
    memset(buf, 0, size);
    return buf;
}

int parse_filename(char *filename, char **name, char **extend)
{
    if (filename == NULL) 
        return 1;
    *name = *extend = NULL;
    int idx = -1;
    char *w = filename;
    for ( ; *w; w++) 
        if (*w == '.')
            idx = w - filename;
    if (idx == -1) 
        *name = strdup(filename);
    else {
        *name = exmallocc(idx);
        memcpy(*name, filename, idx);
        *extend = strdup(filename + idx + 1);
    }    
    return 0;
}
