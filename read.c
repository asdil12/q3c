
#include <stdio.h>
#include "q3c.h"
#include "backlog.h"

#define IR_DEVICE "/dev/ttyUSB0"

int main()
{
	int ir;
	float t0_value;
	float t0_power;
	backlog_init();
	if ((ir = q3c_init(IR_DEVICE)) < 0)
		return 1;

	for (;;) {
		if ((t0_value = q3c_read(ir)) < 0) {
			q3c_cleanup(ir);
			return 1;
		}
		if (t0_value > backlog_last_value()) {
			backlog_append(t0_value);
			printf("T0 Value: %.2fkWh\n", t0_value);
			if ((t0_power = backlog_calc_power()) > 0) {
				printf("T0 Power: %.1fW\n", t0_power);
			}
		}
	}

	q3c_cleanup(ir);
	return 0;
}
