#ifndef CONFIG_H
#define CONFIG_H

struct configuration {
	char* ir_device;
	char* status_dir;
	unsigned int backlog_min_timespan;
};

extern struct configuration config;

int config_init(const char* configfile);
void config_cleanup();

#endif
