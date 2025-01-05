#ifndef SRC_SENSORS_DS18B20_H_
#define SRC_SENSORS_DS18B20_H_

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>

int DS18B20ProbeThread();

#endif // SRC_SENSORS_DS18B20_H_