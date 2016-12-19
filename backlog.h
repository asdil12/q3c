#ifndef BACKLOG_H
#define BACKLOG_H

#include <time.h>

struct backlog_entry {
	time_t timestamp;
	float value;
} backlog[256];

unsigned char backlog_pos;

void backlog_init();
void backlog_append(float value);
void backlog_append_t(float value, time_t timestamp);
float backlog_calc_power();
float backlog_last_value();

#endif
