#ifndef __XML_H_
#define __XML_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <zip.h>

#include "xl.h"

char **string_table(zip_t *archive);
char *sheet_file(zip_t *archive, char *sheet_name);
char *export_csv(zip_t *archive, char *sheet_file, coord_t *start, coord_t *end);

#ifdef __cplusplus
}
#endif

#endif // __XML_H_
