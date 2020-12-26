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

dev_t dev = 0;
static struct class *dev_class;
static struct cdev scull_cdev;

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
		printk ("char dev alloc failed and major no not allocated\n");
		return -1;
	}

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
		class_destroy(dev_class);
		unregister_chrdev_region(dev, 1);
		return -1;
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
