#include <stdio.h>
#include "q3c.h"
#include "backlog.h"
#include "config.h"
#include "status.h"

int main()
{
	int ir;
	float t0_value, t0_power;
	float t0_last_value = 0;
	const char* cfgfile = "/etc/readq3c.cfg";
	if (config_init(cfgfile) < 0) {
		fprintf(stderr, "Can't load config '%s'\n", cfgfile);
		return 1;
	}
	backlog_init();

	if ((ir = q3c_init(config.ir_device)) < 0)
		return 1;

	if (status_init(config.status_dir) < 0)
		return 1;

	for (;;) {
		if ((t0_value = q3c_read(ir)) < 0) {
			config_cleanup();
			q3c_cleanup(ir);
			return 1;
		}
		if (t0_value > t0_last_value) {
			printf("T0 Value: %.2fkWh\n", t0_value);
			status_writef("value", "%.2f\n", t0_value);
			// Skip backlog for 1st value to prevent inaccurate (too small) time intervals
			// resulting in power values for the first calculations
			if (t0_last_value) {
				backlog_append(t0_value);
				if ((t0_power = backlog_calc_power()) > 0) {
					printf("T0 Power: %.1fW\n", t0_power);
					status_writef("power", "%.1f\n", t0_power);
					status_writef2("json", "{\"power\": %.1f, \"value\": %.2f}\n", t0_power, t0_value);
				}
			}
			fflush(stdout);
			t0_last_value = t0_value;
		}
	}

	status_cleanup();
	config_cleanup();
	q3c_cleanup(ir);
	return 0;
}
