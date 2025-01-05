#include "DataTypes.h"
#include "DHT11.h"

static const struct device *DHT11DevPtr = DEVICE_DT_GET(DT_ALIAS(dth11tmp));
extern struct k_msgq SensorDataQueue;

void ThreadDHT11(void)
{
	int returnVal;

	if (!DHT11DevPtr) {
		printf("No DHT11 device found!\n");
	}
	
	if (!device_is_ready(DHT11DevPtr)) {
		printf("Device %s is not ready\n", DHT11DevPtr->name);
	}

	struct sensor_value Temperature;
    struct sensor_value Humidity;

	struct data_item_type QueuePut;

	while (1) {

        returnVal = sensor_sample_fetch(DHT11DevPtr);

		if(!returnVal)
		{
			returnVal = sensor_channel_get(DHT11DevPtr, SENSOR_CHAN_AMBIENT_TEMP, &Temperature);

			if(!returnVal)
			{
				printk("Temperature: %d.%06d\n", Temperature.val1, Temperature.val2);
			}
			else
			{
				printk("Error Getting Temperature: %d\n", returnVal);
			}
		
			returnVal = sensor_channel_get(DHT11DevPtr, SENSOR_CHAN_HUMIDITY, &Humidity);

			if(!returnVal)
			{
				QueuePut.data = Humidity.val1;
				QueuePut.id = 1;
				printk("Humidity: %d.%06d\n", Humidity.val1, Humidity.val2);
				k_msgq_put(&SensorDataQueue,&QueuePut,K_NO_WAIT); 
			}
			else
			{
				printk("Error Getting Humidity: %d\n", returnVal);
			}

		}
		else{
			printk("Error Getting Sample: %d\n", returnVal);
		}
		
		//k_yield();
	    k_msleep(1500);
		//k_busy_wait(1000000);		
	}
}