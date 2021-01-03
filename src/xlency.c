#include <stdio.h>
#include <zip.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <config.h>
#include <signal.h>

#include "xml.h"

static void catch_function(int signo)
{
	;
}
void version()
{
	printf("%s", PACKAGE_STRING "\nCopyright (C) 2020-2021 Barthandelous01\n\
License RBSD 3-Clause License.\n\
This is free software; you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n");
	 exit(0);
}

void usage()
{
	printf("%s", "\
The Excel file decoder.\n\
\n\
USAGE:\n\
    xlency [Vh] [fose]\n\
\n\
OPTIONS:\n\
    -V, --version       Print the version of the software ane exit\n\
    -h, --help          Print this message and exit\n\
    -f, --file          Input Excel file\n\
    -o, --outfile       Output `csv` file\n\
    -s, --start         Start coordinate for the Excel file\n\
    -e, --end           End coordinate for the Excel file\n\
    -S, --sheet         Worksheet name for the Excel file\n");
	exit(0);
}

/* main */
int main(int argc, char **argv)
{
	signal(SIGABRT, catch_function);
	static struct option longopts[] = {
	    {"version", no_argument, NULL, 'V'},
	    {"help", no_argument, NULL, 'h'},
	    {"file", required_argument, NULL, 'f'},
	    {"outfile", required_argument, NULL, 'o'},
	    {"start", required_argument, NULL, 's'},
	    {"end", required_argument, NULL, 'e'},
	    {"sheet", required_argument, NULL, 'S'}
    };

	/* local pseudo-global variables */
	char *start = "A1";
	char *sheet = "Sheet1";
	char *end = "C3";
	char *outfile = "stdout";
	int errp = 0;
	zip_t *archive;
	char **table;
	FILE *out;

	/* arg parsing */
	int ch = 0;
	while ((ch = getopt_long(argc, argv, "VS:hr:o:s:e:f:", longopts, NULL)) != -1) {
		switch (ch) {
			case 'V':
				version();
				break;
			case 'h':
				usage();
				break;
			case 's':
				start = optarg;
				break;
			case 'e':
				end = optarg;
				break;
			case 'S':
				sheet = optarg;
				break;
			case 'o':
				outfile = optarg;
				break;
			case 'f':
				archive = zip_open(optarg, ZIP_RDONLY, &errp);
				if (errp != 0) {
					fprintf(stderr, "%s%s: error code %d\n",
							"Unable to open file ", optarg, errp);
					exit(-1);
				}
				table = string_table(archive);
				break;
			case ':':
				fprintf(stderr, "%s", "Argument requires option.");
				break;
			default:
				fprintf(stderr, "%s", "Unknown argument\n");
				break;
		}
	}
	if (strcmp(outfile, "stdout") == 0)
		out = stdout;
	else {
		out = fopen(outfile, "w");
	}
	char *x = export_csv(archive, sheet_file(archive, sheet), parse_coord(start), parse_coord(end), out, table);
	exit(0);
}
