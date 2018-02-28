#include <stdlib.h>

const char *mr_init_devices[] = {
	"/sys/class/graphics/fb0",

	// Touchscreens
	"/sys/devices/virtual/input*",
	"/sys/devices/virtual/misc/uinput",
	"/sys/bus/spi",
	"/sys/bus/spi/drivers/rm_ts_spidev",
	"/sys/bus/spi/drivers/maxim_sti",
	"/sys/bus/spi/drivers/tlv320aic3xxx",
	"/sys/devices/platform/spi-tegra114.0",
	"/sys/devices/platform/spi-tegra114.3",
	"/sys/devices/platform/tegra12-i2c.3/i2c-3/3-004a*",
	"/sys/bus/platform/drivers/spi-tegra114",
	"/sys/bus/platform/drivers/synaptics_dsx",
	"/sys/bus/hid",
	"/sys/bus/hid/drivers/hid-multitouch",
	"/sys/class/input/input3",
	"/sys/class/input/input3/event3",
	"/sys/class/input/input2",
	"/sys/class/input/input2/event2",
	
	// Buttons
	"/sys/devices/platform/gpio-keys.4",
	"/sys/devices/platform/gpio-keys.4*",
	"/sys/bus/platform/drivers/gpio-keys",
	"/sys/class/tty/ptmx",
	
	// ADB
	"/sys/class/misc/android_adb",
	"/sys/class/android_usb/android0/f_adb",
	"/sys/devices/platform/tegra-otg*",
	
	// Internal SD
	"/sys/block/mmcblk0",
	"/sys/devices/platform/sdhci-tegra.3",
	"/sys/devices/platform/sdhci-tegra.3/mmc_host/mmc0*",
	
	// External SD
	"/sys/block/mmcblk1",
	"/sys/block/mmcblk1p1",
	"/sys/devices/platform/sdhci-tegra.2",
	"/sys/devices/platform/sdhci-tegra.2/mmc_host/mmc1*",
	
	// SD Block Devices
	"/sys/bus/mmc",
	"/sys/bus/mmc/drivers/mmcblk",
	"/sys/bus/sdio/drivers/bcmsdh_sdmmc",
	"/sys/module/mmc_core",
	"/sys/module/mmcblk",
	"/sys/module/sdhci",

	NULL
};
