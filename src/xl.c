#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

struct coord {
    char *x;
    int y;
};

static void slice_str (const char *str, char *buffer, size_t start, size_t end)
{
    size_t j = 0;
    for (size_t i = start; i <= end; ++i) {
        buffer[j++] = str[i];
    }
    buffer[j] = 0;
}

static inline void fatal(const char *error)
{
    fprintf(stderr, "%s: Aborting", error);
    exit(-1);
}

struct coord *parse_coord (char *name)
{
    /*  match the two subgroups. */
    char *re = "([[:alpha:]]*)(\\d*)";
    regex_t *preg;
    if (regcomp(preg, re, 0) != 0)
        fatal ("Error compiling regular expression");

    /* run the regex */
    size_t nmatch = 2;
    regmatch_t *match;
    if (regexec(preg, name, nmatch, match, 0) != 0)
        fatal ("Error parsing coordinate");

    /* init struct */
    struct coord *x = (struct coord*)malloc(sizeof(struct coord));
    if (x != NULL) {

        /* extract first coordinate */
        slice_str (name, x->x, match[1].rm_so, match[1].rm_eo);

        /* extract second coordinate */
        char *buff = malloc(20);
        if (buff != NULL) {
            slice_str (name, buff, match[2].rm_so, match[2].rm_eo);
            x->y = atoi(buff);
            free(buff);
        } else {
            fatal ("Unable to allocate memory in parse_coord");
        }
    } else {
        fatal ("Unable to allocate memory in parse_coord");
    }
    return x;
}
