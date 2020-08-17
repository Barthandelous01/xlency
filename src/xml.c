#include <zip.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <stdio.h>
#include <stdlib.h>


char **string_table(zip_t *archive)
{
    /* pre-init xml vars */
    xmlDoc *doc;
    xmlNode *root, *node1, *node2;
    xmlChar *key;

    /* read the zip file for the string table */
    zip_file_t *file = zip_fopen(archive, "xl/sharedStrings.xml",
                                 ZIP_FL_UNCHANGED);

    /* stat call */
    struct zip_stat st;
    zip_stat (archive, "xl/sharedStrings.xml", 0, &st);
    char *contents = malloc(st.size+1);
    if (contents == NULL) {
        fprintf(stderr, "%s", "Unable to allocate memory to initialize string table");
        exit(-1);
    }
    /* read */
    zip_fread(file, contents, st.size);

    /* let the XML begin! */
    doc = xmlReadMemory(contents, st.size, "sst", NULL, 0);
    root = xmlDocGetRootElement(doc);

    /* start of allocating for string table */
    int count = atoi(root->properties->next->children->content);
    char **table = malloc(sizeof(char *) * count);

    /* free stuff! $0.00 */
    xmlFreeDoc(doc);

    /* boilerplate */
    return table;
}
