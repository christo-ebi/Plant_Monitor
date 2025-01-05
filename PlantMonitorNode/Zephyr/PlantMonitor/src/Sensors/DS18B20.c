#include "DS18B20.h"
#include "DataTypes.h"

const static struct device *const tempProbeDev = DEVICE_DT_GET(DT_ALIAS(probetemp));

extern struct k_msgq SensorDataQueue;

int DS18B20ProbeThread()
{

    if (tempProbeDev == NULL) {
		printk("\nError: Device %s  found in DT.\n",tempProbeDev->name);
		return -1;
	}

	if (!device_is_ready(tempProbeDev)) {
		printk("\nError: Device \"%s\" is not ready \n", tempProbeDev->name);
		return -1;
	}
   
    int res;

	struct sensor_value temp;

    struct data_item_type QueuePut;

    while(1)
    {

		res = sensor_sample_fetch(tempProbeDev);

		if (res != 0) {
			printk("sample_fetch() failed: %d\n", res);
		}

		res = sensor_channel_get(tempProbeDev, SENSOR_CHAN_AMBIENT_TEMP, &temp);
		if (res != 0) {
			printk("channel_get() failed: %d\n", res);
		}
		
        printk("Temp: %d.%06d\n", temp.val1, temp.val2);

        QueuePut.data = temp.val1;
	    QueuePut.id = 3;
		k_msgq_put(&SensorDataQueue,&QueuePut,K_NO_WAIT);
    }
}
