#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <config.h>

void version()
{
	printf("%s", PACKAGE_STRING "\nCopyright (C) 2020 Barthandelous01\n\
License RBSD 3-Clause License.\n\
This is free software; you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.");
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
    -x, --xml           Leave temp XML files in current directory\n\
    -f, --file          Input Excel file\n\
    -o, --outfile       Output `csv` file\n\
    -s, --start         Start coordinate for the Excel file\n\
    -e, --end           End coordinate for the Excel file\n\
    -S, --sheet         Worksheet name for the Excel file\n");
	exit(0);
}

/* Global settings */
char *start = "A1";
char *end = "C3";
int xml = 0;
char *outfile = "a.csv";
char *file = "a.xlsx";

/* main */
int main(int argc, char **argv)
{
	static struct option longopts[] = {
	{"version", no_argument, NULL, 'V'},
	{"help", no_argument, NULL, 'h'},
	{"xml", no_argument, NULL, 'x'},
	{"file", required_argument, NULL, 'f'},
	{"outfile", required_argument, NULL, 'o'},
	{"start", required_argument, NULL, 's'},
	{"end", required_argument, NULL, 'e'}
};
	int ch = 0;
	while ((ch = getopt_long(argc, argv, "Vhxr:o:s:e:", longopts, NULL)) != -1) {
		switch (ch) {
			case 'V':
				version();
				break;
			case 'h':
				usage();
				break;
		}
	}
	printf("Excel software! Yay!\n");
	return 0;
}
	
