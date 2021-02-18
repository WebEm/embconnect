// SPDX-License-Identifier: GPL-2.0+
/*
 * 2021+ Copyright (c) WebEm <embconnect001@gmail.com>
 * All rights reserved.
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>

static unsigned long int phy_start_addr = 0x10000000;
static char *string = "0xdeadbeef";
static int array[3] = { 0, 1, 2 };
static int argc = 0;

/*
 * module_param(foo, int, 0000)
 * First param is the parameter name
 * The second param is the data type.
 * The third param is the permission bits
 */

/*
 * Example to get long int from command line
 */
module_param(phy_start_addr, long, 0660);
MODULE_PARM_DESC(phy_start_addr, "Variable stores the DDR PHY start addr");

/*
 * Example to get string from command line
 */
module_param(string, charp, 0660);
MODULE_PARM_DESC(mystring, "A character string");

/*
 * Example to get int array from command line
 */

/*
 * module_param_array(name, type, num, perm);
 * The first param is the parameter's (in this case the array's) name
 * The second param is the data type of the elements of the array
 * The third argument is a pointer to the variable that will store the number
 * of elements of the array initialized by the user at module loading time
 * The fourth argument is the permission bits
 */

module_param_array(array, int, &argc, 0660);
MODULE_PARM_DESC(myintArray, "An array of integers");

/*
 * To execute with commonad line arguments syntax needs to be
 * is "insmod <xxx.ko> var_name=val <space> var_name=val
 * For this example programm the command will be
 * 'insmod module_params.ko \
 * phy_start_addr=0x2000000 string="kernelProgramming" array=4,5,6'
 */

static int __init module_param_init(void)
{
	int i;
	printk("%s %d\n", __func__, __LINE__);
	printk(KERN_INFO "phy start addr 0x%lx\n", phy_start_addr);
	printk(KERN_INFO "string fed %s\n", string);
	for (i = 0; i < (sizeof(array) / sizeof (int)); i++)
	{
		printk(KERN_INFO "Array[%d] = %d\n", i, array[i]);
	}
	printk(KERN_INFO "got %d arguments for Array.\n", argc);
	return 0;
}

static void __exit module_param_exit(void)
{
	printk("%s %d\n", __func__, __LINE__);

}

module_init(module_param_init);
module_exit(module_param_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("WebEm");
