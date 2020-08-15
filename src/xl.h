#ifndef __XL_H_
#define __XL_H_

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct coord {
        char *x;
        int y;
    } coord_t;

    struct coord *parse_coord (char *name);

    int *range_int (size_t start, size_t end);

#ifdef __cplusplus
}
#endif

#endif // __XL_H_
