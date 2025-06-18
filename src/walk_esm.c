#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"
#include "stack.h"
#include "myread.h"
#include "walk_esm.h"
#include "DialEntry.h"
#include "walk_string.h"

#define WALK(fp, offset) fseek((fp), (offset), SEEK_SET)

static FILE *str_fp;
static int strings_flag;
static uint32_t walksize = 0;

void walk_esmset(char *filename, int flag)
{
    if (flag == 0)
        stackinit();
    str_fp = fopen(filename, "rb");
}

void walk_esmend()
{
    if (str_fp)
        fclose(str_fp);
    walksize = 0;
    strings_flag = 0;
}

void stepp_strategy(int type, int idx, void *stream)
{
    FILE *fp = stream;
    if (idx < 0 || idx > 1) {
        fprintf(stderr, "stepp..... idx is error\n");
        exit(1);
    }
    uint32_t visit, oldsize;
    char buf_temp[5] = { 0 };
    READ(fp, &visit, 4);
    oldsize = visit;
    walksize += visit;

    switch(type) {
        case GRUP:
            READ(fp, buf_temp, 4);
            READ(fp, &visit, 4);

            if (strcmp(buf_temp, "DIAL") != 0)
                WALK(fp, walksize);
            else {
                if (visit != 0) 
                    WALK(fp, walksize);
                walksize += 24;
                walksize -= oldsize;
                WALK(fp, walksize);
            }
            break;
        case TES4:
            visit = 0;
            READ(fp, &visit, 1);
            if ((visit & 0x80) == 0x80) {
                gather_dire(str_fp);
                strings_flag = 1;
            }
            walksize += 24;
            WALK(fp, walksize);
            break;
        case DIAL:
            fseek(fp, -4, SEEK_CUR);
            DialEntry dial = getDial();
            readDial(&dial, idx, fp);
            if (strings_flag && dial.full[idx]) {
                if (str_fp == NULL) {
                    fprintf(stderr, "fp must need but open error\n");
                    exit(1);
                }
                memcpy(&visit, dial.full[idx], 4);          //visit 现在为string中的id
                free(dial.full[idx]);
                getstring(visit, &(dial.full[idx]), str_fp);
            }
            install(&dial);
            walksize += 24;
            WALK(fp, walksize);
            break;
        default:
            printf("\t\tOTHER\n");
            break;
    }
}
