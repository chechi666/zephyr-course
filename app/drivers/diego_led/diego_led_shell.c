#include <zephyr/shell/shell.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/kernel.h>
#include "../../includes/diego_led.h"

const struct device *driver = DEVICE_DT_GET(DT_NODELABEL(diego_led0));


static int sensor_sample_fetch_cmd(const struct shell *sh, size_t argc,
			     char **argv)
{
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);
	sensor_sample_fetch(driver);

	return 0;
}


static int sensor_channel_get_cmd(const struct shell *sh, size_t argc,
			     char **argv)
{
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);
        struct sensor_value val;
	int res = sensor_channel_get(driver, SENSOR_CHAN_AMBIENT_TEMP, &val);
	shell_print(sh, "result, %d",res);

	return 0;
}

static int sensor_info_cmd(const struct shell *sh, size_t argc,
				    char **argv)
{
        ARG_UNUSED(argc);
	ARG_UNUSED(argv);
        bool ready = device_is_ready(driver);
        shell_print(sh, "Device %s ready=%d", driver->name, ready);
        
        return 0;
}

static int sensor_set_cmd(const struct shell *sh, size_t argc,
				    char **argv)
{
        errno = 0;
        char *endptr;
        int val = (int)strtol(argv[1], &endptr, 10);
        if (errno != 0 || *endptr != '\0') {
          shell_error(sh,"<arg> mut be an integer");
          return -EINVAL;
          }
        diego_led_set_valor(driver, val);
        return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sub_sensor,
	SHELL_CMD_ARG(fetch, NULL, "Uses sensor sample fetch", sensor_sample_fetch_cmd, 1, 0),
	SHELL_CMD_ARG(read, NULL, "Uses sensor channel get", sensor_channel_get_cmd, 1, 0),
	SHELL_CMD_ARG(info, NULL, "Print info about sensor", sensor_info_cmd, 1, 0),
	SHELL_CMD_ARG(set, NULL, "Uses sensor API to store <arg> in value", sensor_set_cmd, 2, 0),
	SHELL_SUBCMD_SET_END /* Array terminated. */
);

SHELL_CMD_REGISTER(sensor, &sub_sensor, "Sensor commands", NULL);

