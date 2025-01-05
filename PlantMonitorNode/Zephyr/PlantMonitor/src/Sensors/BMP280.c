#include "DataTypes.h"
#include "BMP280.h"

static const struct device *dev = DEVICE_DT_GET(DT_ALIAS(sensortmp));

extern struct k_msgq SensorDataQueue;


//Create RTIO IO DEV using this MACRO.
SENSOR_DT_READ_IODEV(iodev, DT_NODELABEL(sensor1),
    { SENSOR_CHAN_AMBIENT_TEMP, 0 },
    { SENSOR_CHAN_PRESS, 0 },);

RTIO_DEFINE(cntx,128,128);

int BMP280Thread(void)
{
	int ret;
	uint8_t buf[128];

	uint32_t temp_fit = 0;
	uint32_t press_fit = 0;

	struct sensor_q31_data temp_data = {0};
	struct sensor_q31_data press_data = {0};

	const struct sensor_decoder_api *decoder;

	if (!dev) {
		printf("No BMP280 device found!\n");
		return 0;
	}
	if (!device_is_ready(dev)) {
		printf("Device %s is not ready\n", dev->name);
	}

	struct data_item_type QueuePut;

	while(1) {

		temp_fit = 0;
		press_fit = 0;
	 
		ret = sensor_read(&iodev,&cntx,buf,128);
		
		if(ret <0)
		{
			printf("Sensor Read Failed: %d \n", ret);
			continue;
		}

		ret = sensor_get_decoder(dev,&decoder);
		if(ret <0)
		{
			printf("Sensor Get->Decoder Failed: %d \n", ret);
			continue;
		}

		ret = decoder->decode(buf,(struct sensor_chan_spec){ SENSOR_CHAN_AMBIENT_TEMP, 0 },&temp_fit, 1, &temp_data);
		if(ret <0)
		{
			printf("Sensor Decodeing Failed: %d \n", ret);
			continue;
		}

		ret = decoder->decode(buf,(struct sensor_chan_spec){SENSOR_CHAN_PRESS, 0 },&press_fit, 1, &press_data);
		if(ret <0)
		{
			printf("Sensor Decodeing Failed: %d \n", ret);
			continue;
		}

		QueuePut.data = temp_data.readings[0].temperature;
	    QueuePut.id = 2;
		k_msgq_put(&SensorDataQueue,&QueuePut,K_NO_WAIT);

		printk("Temp: %s%d.%d; Press: %s%d.%d;\n",
		PRIq_arg(temp_data.readings[0].temperature, 6, temp_data.shift),
		PRIq_arg(press_data.readings[0].pressure, 6, press_data.shift));

		k_msleep(1000);
	}
	return 0;
}