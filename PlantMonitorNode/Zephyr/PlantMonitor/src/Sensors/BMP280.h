#ifndef SRC_SENSORS_BMP280_H_
#define SRC_SENSORS_BMP280_H_

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>

int BMP280Thread(void);
#endif // SRC_SENSORS_BMP280_H_
