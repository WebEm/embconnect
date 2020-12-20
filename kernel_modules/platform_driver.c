// SPDX-License-Identifier: GPL-2.0+
/*
 * 2020+ Copyright (c) WebEm <embconnect001@gmail.com>
 * All rights reserved.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>

#define DRV_NAME "platform_dummy_dev"

/*
 * Example program that explains platform driver
 * model. In order to have successful device enemuration
 * the name of the platform driver and the platform device
 * should match.
 *
 * If the driver is not enemurated properly check
 * whether driver/device is registered(/sys/bus/platform/).
 * Check for compatible name in device structure or dts
 * file. The name should map with the platform driver name.
 */
static int platform_probe(struct platform_device *dev)
{
	printk("Platform device enemurated...\n");
	return 0;
}

static int platform_remove(struct platform_device *dev)
{
	printk("platform device removed...");
	return 0;
}

static void tst_device_release(struct device *dev)
{
	printk("Release resources...\n");
}

struct platform_driver test_platform_driver = {
	.probe = platform_probe,
	.remove = platform_remove,
	.driver = {
		.name = DRV_NAME,
		.owner = THIS_MODULE,
	},
};

struct platform_device test_platform_device = {
	.name = DRV_NAME,
	.id = -1,
	.dev = {
		.release = tst_device_release,
	}
};

static int __init platform_init(void)
{

	int ret = 0;
	printk("%s \n", __func__);
	/*
	 * On successful driver registration platform driver
	 * will be visible in /sys/bus/platform/driver.
	 */
	ret = platform_driver_register(&test_platform_driver);
	if (ret != 0) {
		printk("Platform driver registration failed:%d\n", ret);
		return ret;
	}
	printk("Registered platfrom driver....\n");
	/*
	 *  On successful device additon platform device will be
	 *  visible in /sys/bus/platform/device
	 */
	ret = platform_device_register(&test_platform_device);
	if (ret != 0) {
		platform_driver_unregister(&test_platform_driver);
		printk("platform device add failed %d\n", ret);
		return ret;
	}
	return ret;
}

static void __exit platform_exit(void)
{

	printk("%s \n", __func__);
	platform_device_unregister(&test_platform_device);
	platform_driver_unregister(&test_platform_driver);
	printk("De registered platfrom driver....\n");
}

module_init(platform_init);
module_exit(platform_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("WebEm");
