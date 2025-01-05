#ifndef __ZEPHYRPROJECT_ZEPHYR_PROJECTS_PLANTMONITOR_SRC_SENSORS_BMP280_H_
#define __ZEPHYRPROJECT_ZEPHYR_PROJECTS_PLANTMONITOR_SRC_SENSORS_BMP280_H_

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>

int BMP280Thread(void);

#endif // __ZEPHYRPROJECT_ZEPHYR_PROJECTS_PLANTMONITOR_SRC_SENSORS_BMP280_H_