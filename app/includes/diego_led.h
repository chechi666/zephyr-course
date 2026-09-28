#ifndef DIEGO_LED_H
#define DIEGO_LED_H

#include <zephyr/device.h>

#ifdef __cplusplus
extern "C" {
#endif


int diego_led_set_valor(const struct device *dev, int valor);

#ifdef __cplusplus
}
#endif

#endif
