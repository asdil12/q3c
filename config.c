#include <string.h>
#include <stdlib.h>
#include "config.h"
#include "ini.h"

struct configuration config;

int config_handler(void* user, const char* section, const char* name, const char* value)
{
	#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
	if (MATCH("q3c", "ir_device"))
		config.ir_device = strdup(value);
	else if (MATCH("q3c", "backlog_min_timespan"))
		config.backlog_min_timespan = atoi(value);
	else
		return 0;
	return 1;
}

int config_init(const char* configfile)
{
	config.ir_device = NULL;
	if (configfile) {
		return ini_parse(configfile, config_handler, NULL);
	} else {
		return 1;
	}
}

void config_cleanup()
{
	free(config.ir_device);
}

