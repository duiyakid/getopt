#include "pch.h"
#include "getopt.h"
#include <stdio.h>
#include <string.h>

char* optarg = NULL;
int   optind = 1;
int   opterr = 1;
int   optopt = 0;

/* 内部状态 */
static int  nextchar = 1;   /* 当前 argv[optind] 中下一个待检查字符的下标 */

/* 判断 c 是否在 optstring 中，并返回它后面是否跟 ':' */
static const char* find_option(const char* optstring, int c) {
    const char* p = optstring;
    while (*p) {
        if (*p == c) {
            return p;
        }
        p++;
    }
    return NULL;
}

int getopt(int argc, char* const argv[], const char* optstring) {
    optarg = NULL;
    optopt = 0;

    /* 如果上一个选项处理完了，前进到下一个 argv */
    if (nextchar == 1) {
        /* 跳过非选项参数（不以 '-' 开头，或就是 "-"） */
        if (optind >= argc ||
            argv[optind][0] != '-' ||
            argv[optind][1] == '\0') {
            return -1;
        }

        /* 遇到 "--" 终止选项解析 */
        if (strcmp(argv[optind], "--") == 0) {
            optind++;
            return -1;
        }
    }

    /* 取出当前选项字符 */
    int c = argv[optind][nextchar];
    const char* spec = find_option(optstring, c);

    if (c == ':' || spec == NULL) {
        /* 非法选项 */
        optopt = c;
        if (opterr) {
            fprintf(stderr, "%s: invalid option -- '%c'\n", argv[0], c);
        }
        /* 前进到下一个字符或下一个 argv */
        if (argv[optind][++nextchar] == '\0') {
            optind++;
            nextchar = 1;
        }
        return '?';
    }

    /* 判断该选项是否需要参数 */
    if (spec[1] == ':') {
        /* 需要参数 */
        if (argv[optind][nextchar + 1] != '\0') {
            /* 参数紧跟在同一 argv 中，如 -ofile */
            optarg = &argv[optind][nextchar + 1];
            optind++;
            nextchar = 1;
        }
        else if (optind + 1 < argc) {
            /* 参数在下一个 argv 中，如 -o file */
            optarg = argv[optind + 1];
            optind += 2;
            nextchar = 1;
        }
        else {
            /* 缺少参数 */
            optopt = c;
            if (opterr) {
                fprintf(stderr, "%s: option requires an argument -- '%c'\n",
                    argv[0], c);
            }
            optind++;
            nextchar = 1;
            return (optstring[0] == ':') ? ':' : '?';
        }
        return c;
    }

    /* 无参数选项：前进到下一个字符或下一个 argv */
    if (argv[optind][++nextchar] == '\0') {
        optind++;
        nextchar = 1;
    }
    return c;
}