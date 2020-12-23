
// SPDX-License-Identifier: GPL-2.0+
/*
 * 2020+ Copyright (c) WebEm <embconnect001@gmail.com>
 * All rights reserved.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/sysfs.h>

/*
 * Example program explains about creating
 * sysfs entry.
 * sysfs is pseudo file system exported in kernel
 * similar to /proc.
 * This is always mounted to /sys mount point dir
 * The files in /sys contains information about
 * devices and drivers. some files are writable.
 * This is one method of communicating to kernel
 * space from userspace and vice-versa.
 */

struct kobject *kref;
volatile int value = 100;
/*
 * This function is invoked when read variable in /sys
 */
static ssize_t sysfs_show(struct kobject *kobj,
		struct kobj_attribute *attr, char *buf)
{
	printk("%s %d\n", __func__, __LINE__);
	return sprintf(buf, "%d", value);
}

/*
 * This function is invoked when writing to variable in /sys
 */
static ssize_t sysfs_store(struct kobject *kobj,
	struct kobj_attribute *attr,const char *buf, size_t count)
{
	printk(KERN_INFO "Sysfs - Write!!!\n");
	sscanf(buf,"%d",&value);
	return count;
}

struct kobj_attribute sys_attr =
	__ATTR(value, 0666, sysfs_show, sysfs_store);

static int __init sys_example_init(void)
{
	/*
	 * creating a file in /sys/kernel directory.
	 * if you want to create in /sys directory simply
	 * give the second parameter as NULL;
	 * for firmware the parameter is firmware_kobj
	 * refer kernel code for creating kobj in corresponding
	 * subsystem.
	 */
	kref = kobject_create_and_add("sysfs-example", kernel_kobj);
	if (!kref) {
		printk("error in creating Kernel obj\n");
		return -1;
	}

	if(sysfs_create_file(kref, &sys_attr.attr)) {
		printk("sysfs file creation failed\n");
		kobject_put(kernel_kobj);
		return -1;
	}
	return 0;
}

static void __exit sys_example_exit(void)
{
	if (kref)
		kobject_put(kref);

	sysfs_remove_file(kernel_kobj, &sys_attr.attr);
	printk("syfs entry removed...\n");

}

module_init(sys_example_init);
module_exit(sys_example_exit)
MODULE_LICENSE("GPL");
MODULE_AUTHOR("WebEm");
