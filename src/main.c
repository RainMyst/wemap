#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"
#include "myread.h"
#include "extext.h"
#include "walk_esm.h"
#include "DialEntry.h"

static int initflag;
static char *buf[4];


int parse_argv(int argc, char **argv)
{
    if (argc == 1) {
        fprintf(stderr, "argc is error\n");
        exit(1);
    }
    for (argv++; *argv; argv++) {
        if (*(*argv)++ == '-') {
            if (**argv == 'E' || **argv == 'C') {
                if (strlen(*argv) == 1) {
                    fprintf(stderr, "*argv is too small\n");
                    exit(1);
                }
                if (**argv == 'E')
                    buf[1] = *argv + 1;
                else
                    buf[0] = *argv + 1;
            } else if (**argv == 'S') {
                if (strlen(*argv) < 3) {
                    fprintf(stderr, "*argv is too small\n");
                    exit(1);
                }
                (*argv)++;
                if (**argv == 'C')
                    buf[2] = *argv + 1;
                else 
                    buf[3] = *argv + 1;
            }
        }
    }
    if (buf[0] == NULL && buf[1] == NULL) {
        exit(1);
    }

    //设置默认值
    char *name, *extend;
    if (buf[3] == NULL) {
        if (buf[1]) {
            parse_filename(buf[1], &name, &extend);
            buf[3] = exmallocc(strlen(name) + strlen("strings") + 2 + strlen("english"));
            sprintf(buf[3], "%s_english%s%s", name, "." , "strings");
        }
    }
    if (buf[2] == NULL) {
        if (buf[0]) {
            parse_filename(buf[0], &name, &extend);
            buf[2] = exmallocc(strlen(name) + strlen("strings") + 2 + strlen("chinese"));
            sprintf(buf[2], "%s_chinese%s%s", name, ".", "strings");
        }
    }
}

void whileread(char *esm, char *string, int idx)
{
    int type;
    char buf_temp[5] = {0};
    FILE *fp = fopen(esm, "rb");
    if (fp == NULL) {
        fprintf(stderr, "whileread open error\n");
        exit(1);
    }

    if (esm) {
        walk_esmset(string, initflag++);
        while (1) {
            if (fread(buf_temp, 1, 4, fp) != 4) {
                walk_esmend();
                break;
            }
            TYPE_SHARE(type, buf_temp);
            stepp_strategy(type, idx, fp);
        }
    }
}

void whileprint(char **str) 
{
    //暂时来说 str[0] and str[1] can't all NULL;
    DialEntry **array = (DialEntry **) stack_to_array();
    int print_flag = 0;
    int bufp = getbufp();
    printf("{\n");
    if (str[0] == NULL) {   
        for (int i = 0; i < bufp; i++) {
            if (array[i]->full[1] == NULL)
                continue;
            transition(array[i]);
            printf("%s%s  %s", print_flag ? ",": "", print_flag ? "\n": "", array[i]->full[1]);
            print_flag++;
        }
    } else if (str[1] == NULL) {
        for (int i = 0; i < bufp; i++) {
            if (array[i]->full[0] == NULL)
                continue;
            transition(array[i]);
            printf("%s%s  %s", print_flag ? ",": "", print_flag ? "\n": "", array[i]->full[0]);
            print_flag++;
        }
    } else {
        for (int i = 0; i < bufp; i++) {
            if (array[i]->full[0] == NULL || array[i]->full[1] == NULL)
                continue;
            transition(array[i]);
            printf("%s%s%s\"%s\": \"%s\"", print_flag ? ",": "", print_flag ? "\n": "", "  ",array[i]->full[0], array[i]->full[1]);
            print_flag++;
        }
    }
    printf("\n}");
    printf("\n");
}

int main(int argc, char *argv[])
{
    parse_argv(argc, argv);

    if (buf[0])
        whileread(buf[0], buf[2], 0);
    if (buf[1])
        whileread(buf[1], buf[3], 1);

    if (buf[1] || buf[0])
        whileprint(buf); 

    return 0;
}

