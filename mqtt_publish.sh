#!/bin/bash

status_dir=/dev/shm/q3c
host="ikarus.heidler.lan"
user="abc"
pass="123"

power_old=""
value_old=""

while true ; do
	power=$(cat "${status_dir}/power")
	value=$(cat "${status_dir}/value")

	if [[ "$power_old" != "$power" ]] ; then
		mosquitto_pub -h "$host" -u "$user" -P "$pass" -t "q3c/power" -m "$power"
		echo "q3c/power -> $power"
		power_old="$power"
	fi
	if [[ "$value_old" != "$value" ]] ; then
		mosquitto_pub -h "$host" -u "$user" -P "$pass" -t "q3c/value" -m "$value"
		echo "q3c/value -> $value"
		value_old="$value"
	fi
	sleep 1
done
