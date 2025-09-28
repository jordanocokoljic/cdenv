#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <errno.h>

void skip_line(FILE *fp) {
	char ch;
	while ((ch = fgetc(fp)) != EOF && ch != '\n') {}
}

int main(int argc, char *argv[]) {
	char opt, *filename = ".env", *varname, ch;
	FILE *fp;
	int ci, varlen, found = 1;

	while ((opt = getopt(argc, argv, "f:")) != -1) {
		switch (opt) {
			case 'f':
				filename = optarg;
				break;
		}
	}

	if (optind == argc) {
		fprintf(stderr, "No variable name specified\n");
		return 1;
	}

	varname = argv[optind];
	varlen = strlen(varname);

	fp = fopen(filename, "r");
	if (fp == NULL) {
		fprintf(
			stderr, "Error opening dotenv (%s): %s\n",
			filename, strerror(errno)
		);

		return 1;
	}

	while ((ch = fgetc(fp)) != EOF) {
		if (ch == '=') {
			if (ci == varlen) {
				while ((ch = fgetc(fp)) != EOF && ch != '\n') {
					printf("%c", ch);
				}

				found = 0;
				break;
			}

			ci = 0;
			skip_line(fp);
		}

		if (ci < varlen) {
			if (ch == varname[ci]) {
				ci++;
				continue;
			}

			ci = 0;
			skip_line(fp);
		}
	}

	fclose(fp);
	return found;
}
