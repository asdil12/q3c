#include "backlog.h"
#include <stdio.h>

#define BACKLOG_MIN_TIMESPAN 300

void backlog_init()
{
	int i;
	for (i=0; i<256; i++) {
		backlog[i].timestamp = 0;
	}
	backlog_pos = -1;
}

void backlog_append_t(float value, time_t timestamp)
{
	backlog_pos++;
	backlog[backlog_pos].timestamp = timestamp;
	backlog[backlog_pos].value = value;
}

void backlog_append(float value)
{
	backlog_append_t(value, time(NULL));
}

float backlog_calc_power()
{
	int i;
	struct backlog_entry diff;
	for (i=1; i<256; i++) {
		struct backlog_entry *be = backlog + (backlog_pos - i);
		if (be->timestamp && be->timestamp < backlog[backlog_pos].timestamp) {
			if (be->timestamp <= (backlog[backlog_pos].timestamp - BACKLOG_MIN_TIMESPAN)) {
				// we got what we want
				break;
			}
		} else {
			// BACKLOG_MIN_TIMESPAN not available yet
			// --> take what we currently have
			i--;
			break;
		}
	}
	if (i == 0) {
		// backlog is empty
		return -1;
	}
	//printf("backlog_calc_power - i = %i\n", i);
	diff.timestamp = backlog[backlog_pos].timestamp - backlog[backlog_pos-i].timestamp;
	diff.value = backlog[backlog_pos].value - backlog[backlog_pos-i].value;
	//printf("diff.timestamp: %li\n", diff.timestamp);
	//printf("diff.value: %.2f\n", diff.value);

	return (diff.value * 1000 * 3600) / diff.timestamp;
}

float backlog_last_value()
{
	if (backlog[backlog_pos].timestamp) {
		return backlog[backlog_pos].value;
	} else {
		return -1;
	}
}
