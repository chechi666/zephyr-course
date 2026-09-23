#include<zephyr/init.h>
#include<zephyr/kernel.h>
#include<zephyr/sys/printk.h>

static int board_esp32_from_scratch_init(void) {
  /* Some function to run before boot */
  printk("Board Initialized");
  return(0);
}

SYS_INIT(board_esp32_from_scratch_init, POST_KERNEL, 0);
