#ifndef __XL_H_
#define __XL_H_

struct coord {
    char *x;
    int y;
};

struct coord *parse_coord (char *name);

#endif // __XL_H_
