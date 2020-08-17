#ifndef __XML_H_
#define __XML_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <zip.h>

char **string_table(zip_t *archive);
char *sheet_file(zip_t *archive, char *sheet_name);

#ifdef __cplusplus
}
#endif

#endif // __XML_H_
