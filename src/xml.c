#include <zip.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "xl.h"
#include "chars.hpp"

static char *zip_read(zip_t *archive, char *name, int *size)
{
    zip_file_t *file = zip_fopen(archive, name, ZIP_FL_UNCHANGED);

    struct zip_stat st;
    zip_stat (archive, name, 0, &st);
    char *contents = malloc(st.size+1);
    if (contents == NULL) {
        fprintf(stderr, "%s\n", "Unable to allocate memory");
        exit(-1);
    }

    *size = st.size;

    zip_fread(file, contents, st.size);

    return contents;
}

char **string_table(zip_t *archive)
{
    /* pre-init xml vars */
    xmlDoc *doc;
    xmlNode *root, *node1;

    int size;
    char *contents = zip_read(archive, "xl/sharedStrings.xml", &size);

    /* let the XML begin! */
    doc = xmlReadMemory(contents, size, "sst", NULL, 0);
    root = xmlDocGetRootElement(doc);

    /* start of allocating for string table */
    int count = atoi(root->properties->children->content);
    char **table = malloc(sizeof(char *) * count);

    int index = 0;
    char *temp;
    for (node1 = root->children; node1 != NULL; node1 = node1->next) {
        temp = (char *)xmlNodeGetContent(node1->children);
        table[index] = malloc(strlen(temp));
        strcpy(table[index], temp);

        index++;
    }

    /* free stuff! $0.00 */
    free(contents);
    xmlFreeDoc(doc);

    /* boilerplate */
    return table;
}

char *sheet_file(zip_t *archive, char *sheet_name)
{
    /* XML boilerplate */
    xmlDoc *doc;
    xmlNode *root, *node1, *node2;

    int size;
    char *contents = zip_read(archive, "xl/workbook.xml", &size);

    int id;

    doc = xmlReadMemory(contents, size, "workbook", NULL, 0);
    root = xmlDocGetRootElement(doc);

    node1 = root->children;
    for (; node1 != NULL; node1 = node1->next) {
        if (xmlStrcmp(node1->name, (const xmlChar *)"sheets") == 0) {
            for (node2 = node1->children; node2 != NULL; node2 = node2->next) {
                if (xmlStrcmp(node2->properties->children->content, (const xmlChar *)sheet_name) == 0) {
                    id = atoi(node2->properties->next->children->content);
                }
            }
        }
    }

    char *buff = malloc(27);
    sprintf(buff, "xl/worksheets/sheet%d.xml", id);

    /* free boilerplate */
    free(contents);
    xmlFreeDoc(doc);

    return buff;
}

static inline xmlNode *next_node_by_name (char *name, xmlNode *node)
{
  xmlNode *node2;
  for (node2 = node->children; (node2 != NULL) && (xmlStrcmp(node2->name, (xmlChar *)name)); node2 = node2->next)
    ;
   return node2;
 }

/*
 * Despite the whole "no more than 7 things" rule, this is still understandable.
 * It is, unfortunately, basically tree walking code that couldn't be genericed.
 */
char *export_csv(zip_t *archive, char *sheet_file,
		 coord_t *start, coord_t *end, FILE *fp, char **table)
{
    xmlDoc *doc;
    xmlNode *root, *node1, *node2, *node3;

    int size;
    char *contents = zip_read(archive, sheet_file, &size);

    char buff[40];
    char digit[20];

    int *y = range_int(start->y, end->y);
    int len_y = end->y - start->y + 1;
    char **x = sequence(start->x, end->x);
    int len_x = row_to_int(end->x) - row_to_int(start->x) + 1;

    /* xml boilerplate */
    doc = xmlReadMemory(contents, size, "worksheet", NULL, 0);
    root = xmlDocGetRootElement(doc);
    char *key;
    node1 = next_node_by_name ("sheetData", root);

    int found = 0;
    // counter loops from x to y
    for (int count_y = 0; count_y < len_y; count_y++) {
      for (int count_x = 0; count_x < len_x; count_x++) {
	// The xml is structured so that I need to move to the next node already.
	node2 = node1->children;

	// set up buffers
	sprintf(buff, "%s%d", x[count_x], y[count_y]);
	sprintf(digit, "%d", y[count_y]);
	for (node2 = node1->children; (node2 != NULL); node2 = node2->next) {
	  if (xmlStrcmp(node2->properties->children->content, (xmlChar *)digit) != 0)
	    continue;
	  found = 0;
	  for (node3 = node2->children; node3 != NULL; node3 = node3->next) {
	    if (xmlStrcmp(node3->properties->children->content, (xmlChar *)buff) == 0) {
	      found = 1;
	      if ((node3->properties->next != NULL)) {
		if (xmlStrcmp(node3->properties->next->children->content, (xmlChar *)"s") == 0) {
		  key = (char *)xmlNodeGetContent(node3->children);
		  if (count_x != len_x - 1) {
		    fprintf(fp, "%s,", table[atoi(key)]);
		  } else {
		    fprintf(fp, "%s\n", table[atoi(key)]);
		  }
		  xmlFree(key);
		  continue;
		}
	      } else {
		key = (char *)xmlNodeGetContent(node3->children);
		if (count_x != len_x - 1) {
		  fprintf(fp, "%s,", key);
		} else {
		  fprintf(fp, "%s\n", key);
		}
		xmlFree(key);
		continue;
	      }
	    }
	  }
	  if (found == 0) {
	    if (count_x != len_x - 1)
	      fprintf(fp, "%s", ",");
	    else
	      fprintf(fp, "%s\n", ",");
	  }
	  fflush(stdout);
	  break;
	}
      }
    }

    /* free & return */
    for (int i = 0; i < len_x; i++) {
        free(x[i]);
    }
    free(x);
    free (y);
    free(contents);
    xmlFreeDoc(doc);
    return "";
}
