/*
 *   simple_init.c
 * 
 * 2016+ Copyright (c) WebEm <embconnect001@gmail.com>
 * All rights reserved.
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
/*
 * simple_init.c program to demonstrate how the module gets
 * inserted in to the kernel. 
 * Call flow comment will be added in the upcomming CL's.
 * like how the module_init gets invoked... etc....!!
 */
#include <linux/init.h>
#include <linux/module.h>

static int __init webem_init(void)
{
	printk ("%s\n", __func__);
	return 0;
}

static void __exit webem_exit(void)
{
	printk ("%s\n", __func__);
}

module_init(webem_init);
module_exit(webem_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("WebEm");
