#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>


#define DT_DRV_COMPAT diego_led

#define LED_ROJO_NODE DT_NODELABEL(red_led)
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED_ROJO_NODE, gpios);



LOG_MODULE_REGISTER(diego_led, LOG_LEVEL_INF);


static int channel_get_my_impl(const struct device *dev,
				enum sensor_channel chan,
				struct sensor_value *val) {
	LOG_INF("Hello From Channel Get, channel %d", chan);
	gpio_pin_set_dt(&led2,0);
	return 0;
}

static int sample_fetch_my_impl(const struct device *dev,
				enum sensor_channel chan) {
	LOG_INF("Hello From Sample Fetch, channel %d", chan);
	gpio_pin_set_dt(&led2,1);
	return 0;
}


static DEVICE_API(sensor, api_diego_curso) = {
	.channel_get = channel_get_my_impl,
	.sample_fetch = sample_fetch_my_impl,
};

static int init(const struct device *dev) {
	if (gpio_pin_configure_dt(&led2, GPIO_OUTPUT_ACTIVE) < 0) return 0;
	LOG_INF("Device Initialized!");
	return 0;
}

DEVICE_DT_INST_DEFINE(0, init, NULL, NULL, NULL, POST_KERNEL, 80, &api_diego_curso);
