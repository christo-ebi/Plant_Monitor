#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>

#include "DataTypes.h"
#include "DHT11.h"
#include "BMP280.h"
#include "DS18B20.h"

#define DHT11_PRIORITY 7
#define BMP280_PRIORITY 7
#define DS18B20_PRIORITY 7

#define DHT11_STACKSIZE 1024
#define BMP280_STACKSIZE 1024
#define DS18B20_STACKSIZE 1024


static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

K_MSGQ_DEFINE(SensorDataQueue, sizeof(struct data_item_type), 25, 4);


int main(void)
{
	int ret;
	
	struct data_item_type QueueGet;

	if (!gpio_is_ready_dt(&led0)) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);

	if (ret < 0) {
		printk("LED device not ready: %d \n",ret);
	}
	while(1) 
	{
		k_msgq_get(&SensorDataQueue,&QueueGet,K_NO_WAIT);
		printk("Inside Main Loop Data: %d ID: %d\n", QueueGet.data,QueueGet.id);
		printk("Free Space in Queue: %d \n", k_msgq_num_free_get(&SensorDataQueue));

		gpio_pin_toggle_dt(&led0);
		k_msleep(500);
	}
	return 0;
}


K_THREAD_DEFINE(dht11TID,   DHT11_STACKSIZE,   ThreadDHT11,        NULL, NULL, NULL,DHT11_PRIORITY,   0, 0);
K_THREAD_DEFINE(bmp280TID,  BMP280_STACKSIZE,  BMP280Thread,       NULL, NULL, NULL,BMP280_PRIORITY,  0, 0);
K_THREAD_DEFINE(DS18B20TID, DS18B20_STACKSIZE, DS18B20ProbeThread, NULL, NULL, NULL,DS18B20_PRIORITY, 0, 0);
