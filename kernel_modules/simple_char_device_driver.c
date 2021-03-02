// SPDX-License-Identifier: GPL-2.0+
/*
 * 2020+ Copyright (c) WebEm <embconnect001@gmail.com>
 * All rights reserved.
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/kdev_t.h>

#define DEVICE_NAME "chardevice"
dev_t dev = 0;
static struct class *dev_class;
static struct cdev scull_cdev;
static struct device *char_device = NULL;
static int major_number;

/*
 * This function is invoked when the device node is opened
 * from userspace.
 */
static int scull_open(struct inode *ino, struct file *file)
{
	printk("%s %d\n", __func__, __LINE__);
	return 0;
}

/*
 * This function is invoked when the device node is closed
 * from userspace.
 */
static int scull_close(struct inode *ino, struct file *file)
{
	printk("%s %d\n", __func__, __LINE__);
	return 0;
}

/*
 * This function is invoked when the device node is read
 * from userspace using read system call.
 */
static ssize_t scull_read(struct file *fp,
		char __user *buff, size_t size, loff_t *off)
{
	printk("%s %d\n", __func__, __LINE__);
	return 0;
}

/*
 * This function is invoked when the device node is written
 * from userspace using write system call.
 */
static ssize_t scull_write(struct file *fp,
		const char *buf, size_t size, loff_t *off)
{
	printk("%s %d\n", __func__, __LINE__);
	return 0;
}

static struct file_operations fops = {
	.open = scull_open,
	.release = scull_close,
	.write = scull_write,
	.read = scull_read,
	.owner = THIS_MODULE,
};

static int __init chr_dev_init(void)
{
	printk("%s %d\n",
		__func__, __LINE__);
	/**
	 * alloc_chrdev_region() - register a range of char device numbers
	 * @dev: output parameter for first assigned number
	 * @baseminor: first of the requested range of minor numbers
	 * @count: the number of minor numbers required
	 * @name: the name of the associated device or driver
	 *
	 * Allocates a range of char device numbers.  The major number will be
	 * chosen dynamically, and returned (along with the first minor number)
	 * in @dev.  Returns zero or a negative error code.
	 */

	if (alloc_chrdev_region(&dev, 0 ,1, "scull_dev") < 0) {
		printk("char dev alloc failed and major no not allocated\n");
		return -1;
	}
	major_number = MAJOR(dev);
	printk("Major number allocated is %d\n", major_number);

	/**
	 * cdev_init() - initialize a cdev structure
	 * @cdev: the structure to initialize
	 * @fops: the file_operations for this device
	 *
	 * Initializes @cdev, remembering @fops, making it ready to add to the
	 * system with cdev_add().
	 */

	cdev_init(&scull_cdev, &fops);

	/**
	 * cdev_add() - add a char device to the system
	 * @p: the cdev structure for the device
	 * @dev: the first device number for which this device is responsible
	 * @count: the number of consecutive minor numbers corresponding to this
	 *         device
	 *
	 * cdev_add() adds the device represented by @p to the system, making it
	 * live immediately.  A negative error code is returned on failure.
	 */

	if (cdev_add(&scull_cdev, dev, 1) < 0) {
		printk("can't add device to system\n");
		unregister_chrdev_region(dev, 1);
		return -1;
	}

	/**
	 * class_create - create a struct class structure
	 * @owner: pointer to the module that is to "own" this struct class
	 * @name: pointer to a string for the name of this class.
	 *
	 * This is used to create a struct class pointer that can then be used
	 * in calls to device_create().
	 *
	 * Returns &struct class pointer on success, or ERR_PTR() on error.
	 *
	 * Note, the pointer created here is to be destroyed when finished by
	 * making a call to class_destroy().
	 */

	if ((dev_class = class_create(THIS_MODULE, "sys_class")) == NULL) {
		printk("can't create device \n");
		unregister_chrdev_region(dev, 1);
		return PTR_ERR(dev_class);
	}

	/**
	 * device_create - creates a device and registers it with sysfs
	 * @class: pointer to the struct class that this device should be registered to
	 * @parent: pointer to the parent struct device of this new device, if any
	 * @devt: the dev_t for the char device to be added
	 * @drvdata: the data to be added to the device for callbacks
	 * @fmt: string for the device's name
	 *
	 * This function can be used by char device classes.  A struct device
	 * will be created in sysfs, registered to the specified class.
	 *
	 * A "dev" file will be created, showing the dev_t for the device, if
	 * the dev_t is not 0,0.
	 * If a pointer to a parent struct device is passed in, the newly created
	 * struct device will be a child of that device in sysfs.
	 * The pointer to the struct device will be returned from the call.
	 * Any further sysfs files that might be required can be created using this
	 * pointer.
	 *
	 * Returns &struct device pointer on success, or ERR_PTR() on error.
	 *
	 * Note: the struct class passed to this function must have previously
	 * been created with a call to class_create().
	 */
	char_device = device_create(dev_class, NULL, MKDEV(major_number, 0), NULL, DEVICE_NAME);
	if (IS_ERR(char_device)) {
		class_destroy(dev_class);
		unregister_chrdev_region(dev, 1);
		printk(KERN_ALERT "Failed to create the device node\n");
		return PTR_ERR(char_device);

	}

	return 0;
}

static void __exit chr_dev_exit(void)
{
	device_destroy(dev_class, dev);
	class_destroy(dev_class);
	cdev_del(&scull_cdev);
	unregister_chrdev_region(dev, 1);
	printk("char device driver removed....\n");

}

module_init(chr_dev_init);
module_exit(chr_dev_exit);
MODULE_AUTHOR("WebEm");
MODULE_LICENSE("GPL");
