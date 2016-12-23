#include <stdio.h>
#include "q3c.h"
#include "backlog.h"

#define IR_DEVICE "/dev/ttyUSB0"

int main()
{
	int ir;
	float t0_value, t0_power;
	float t0_last_value = 0;
	backlog_init();

	if ((ir = q3c_init(IR_DEVICE)) < 0)
		return 1;

	for (;;) {
		if ((t0_value = q3c_read(ir)) < 0) {
			q3c_cleanup(ir);
			return 1;
		}
		if (t0_value > t0_last_value) {
			printf("T0 Value: %.2fkWh\n", t0_value);
			// Skip backlog for 1st value to prevent inaccurate (too small) time intervals
			// resulting in power values for the first calculations
			if (t0_last_value) {
				backlog_append(t0_value);
				if ((t0_power = backlog_calc_power()) > 0) {
					printf("T0 Power: %.1fW\n", t0_power);
				}
			}
			fflush(stdout);
			t0_last_value = t0_value;
		}
	}

	q3c_cleanup(ir);
	return 0;
}
