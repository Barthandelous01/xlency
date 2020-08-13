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

static void debug_print(char *print)
{
    #ifdef TESTING
    fprintf(stderr, "%s\n", print);
    #endif
}

struct coord *parse_coord (char *name)
{
    debug_print("starting");
    /*  match the two subgroups. */
    char *re = "([[:alpha:]]*)(\\d*)";
    regex_t preg;
    debug_print("compiling regex");
    if (regcomp(&preg, re, REG_EXTENDED) != 0)
        fatal ("Error compiling regular expression");

    /* run the regex */
    size_t nmatch = 3;
    regmatch_t *match;
    debug_print("running regex");
    if (regexec(&preg, name, nmatch, match, 0) != 0)
        fatal ("Error parsing coordinate");

    /* init struct */
    debug_print("making struct");
    struct coord *x = (struct coord*)malloc(sizeof(struct coord));
    if (x != NULL) {

        /* extract first coordinate */
        debug_print("starting first coord");
        slice_str (name, x->x, match[1].rm_so, match[1].rm_eo);
        debug_print(x->x);

        /* extract second coordinate */
        char *buff = malloc(20);
        if (buff != NULL) {
            debug_print("second coord");
            slice_str (name, buff, match[2].rm_so, match[2].rm_eo);
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

#ifdef TESTING
int main()
{
    struct coord *x = parse_coord("A5");
    printf("%s:%d\n", x->x, x->y);
}
#endif // TESTING
