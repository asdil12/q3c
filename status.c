#define _GNU_SOURCE
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include "status.h"

char* status_dir;

int status_init(const char *sd)
{
	status_dir = strdup(sd);
	if (mkdir(status_dir, 0755) == -1) {
		if (errno != EEXIST) {
			perror("mkdir");
			return -1;
		}
		else {
			status_unlink("value");
			status_unlink("power");
		}
	}
	return 0;
}

void status_unlink(const char *fn)
{
	char *status_file;
	asprintf(&status_file, "%s/%s", status_dir, fn);
	unlink(status_file);
	free(status_file);
}

void status_write(const char *fn, const char *content)
{
	char *status_file;
	asprintf(&status_file, "%s/%s", status_dir, fn);
	FILE *f = fopen(status_file, "w");
	fprintf(f, "%s", content);
	fclose(f);
	free(status_file);
}

void status_writef(const char *fn, const char *fmt, float value)
{
	char *fval;
	asprintf(&fval, fmt, value);
	status_write(fn, fval);
	free(fval);
}

void status_writef2(const char *fn, const char *fmt, float value1, float value2)
{
	char *fval;
	asprintf(&fval, fmt, value1, value2);
	status_write(fn, fval);
	free(fval);
}

void status_cleanup()
{
	free(status_dir);
	status_dir = NULL;
}
