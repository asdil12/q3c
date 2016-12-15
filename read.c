
#include <stdio.h>
#include "q3c.h"

#define IR_DEVICE "/dev/ttyUSB0"

int main()
{
	int ir = q3c_init(IR_DEVICE);
	float t0_value;
	if ((t0_value = q3c_read(ir)) < 0) {
		q3c_cleanup(ir);
		return 1;
	}
	printf("T0 Value: %.2f\n", t0_value);
	q3c_cleanup(ir);
	return 0;
}
