#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

typedef struct coord {
    char *x;
    int y;
} coord_t;

static char *slice_str (const char *str, size_t start, size_t end)
{
    char *buffer = malloc(end-start+1);
    size_t j = 0;
    for (size_t i = start; i <= end; ++i) {
        buffer[j++] = str[i];
    }
    buffer[j] = 0;
    return buffer;
}

static inline void fatal(const char *error)
{
    fprintf(stderr, "%s: Aborting", error);
    exit(-1);
}

coord_t *parse_coord (char *name)
{
    /*  match the two subgroups. */
    char *re = "([[:alpha:]]*)([[:digit:]]*)";
    regex_t preg;
    if (regcomp(&preg, re, REG_EXTENDED) != 0)
        fatal ("Error compiling regular expression");

    /* run the regex */
    size_t nmatch = 3;
    regmatch_t *match = malloc(sizeof(regmatch_t) * 3);
    if (regexec(&preg, name, nmatch, match, 0) != 0)
        fatal ("Error parsing coordinate");

    /* init struct */
    coord_t *x = (coord_t*)malloc(sizeof(coord_t));
    if (x != NULL) {

        /* extract first coordinate */
        x->x = slice_str (name, match[1].rm_so, match[1].rm_eo-1);

        /* extract second coordinate */
        char *buff = malloc(20);
        if (buff != NULL) {
            buff = slice_str (name, match[2].rm_so, match[2].rm_eo);
            x->y = atoi(buff);
            free(buff);
        } else {
            fatal ("Unable to allocate memory in parse_coord");
        }
    } else {
        fatal ("Unable to allocate memory in parse_coord");
    }
    regfree(&preg);
    return x;
}

int *range_int (size_t start, size_t end)
{
    size_t length = end - start + 1;
    int *ret = malloc(length * sizeof(int));
    for (size_t i = start; i <= end; ++i) {
        ret[i - start] = i;
    }
    return ret;
}


#ifdef TESTING
int main()
{
    coord_t *x = parse_coord("A5");
    printf("%s:%d\n", x->x, x->y);
}
#endif // TESTING
