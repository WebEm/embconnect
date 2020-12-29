// SPDX-License-Identifier: GPL-2.0+
/*
 * 2020+ Copyright (c) WebEm <embconnect001@gmail.com>
 * All rights reserved.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>

#define BUFF_SIZE 1024

char *buff;
static int __init memory_init(void)
{

	/**
	 * kmalloc - allocate memory
	 * @size: how many bytes of memory are required.
	 * @flags: the type of memory to allocate.
	 *
	 * kmalloc is the normal method of allocating memory
	 * for objects smaller than page size in the kernel.
	 *
	 * The @flags argument may be broken in three categories
	 * action modifiers, zone modififers and types
	 */

	/* TYPE FLAGS.........
	 * %GFP_USER - Allocate memory on behalf of user.  May sleep.
	 *
	 * %GFP_KERNEL - Allocate normal kernel ram.  May sleep.
	 *
	 * %GFP_ATOMIC - Allocation will not sleep.  May use emergency pools.
	 *   For example, use this inside interrupt handlers.
	 *
	 * %GFP_HIGHUSER - Allocate pages from high memory.
	 *
	 * %GFP_NOIO - Do not do any I/O at all while trying to get memory.
	 *
	 * %GFP_NOFS - Do not make any fs calls while trying to get memory.
	 *
	 * %GFP_NOWAIT - Allocation will not sleep.
	 *
	 * %__GFP_THISNODE - Allocate node-local memory only.
	 *
	 * %GFP_DMA - Allocation suitable for DMA.
	 *   Should only be used for kmalloc() caches. Otherwise, use a
	 *   slab created with SLAB_DMA.
	 */


	 /*
	 * Also it is possible to set different flags by OR'ing
	 * in one or more of the following additional @flags:
	 *	return 0;
	 *
	 * %__GFP_COLD - Request cache-cold pages instead of
	 *   trying to return cache-warm pages.
	 *
	 * %__GFP_HIGH - This allocation has high priority and may use emergency pools.
	 *
	 * %__GFP_NOFAIL - Indicate that this allocation is in no way allowed to fail
	 *   (think twice before using).
	 *
	 * %__GFP_NORETRY - If memory is not immediately available,
	 *   then give up at once.
	 *
	 * %__GFP_NOWARN - If allocation fails, don't issue any warnings.
	 *
	 * %__GFP_REPEAT - If allocation fails initially, try once more before failing.
	 *
	 * There are other flags available as well, but these are not intended
	 * for general use, and so are not documented here. For a full list of
	 * potential flags, always refer to linux/gfp.h.
	 */

	/*
	 * Listing of the modifiers behind each TYPE flag
	 * GFP_ATOMIC	  __GFP_HIGH
	 * GFP_NOIO	  __GFP_WAIT
	 * GFP_NOFS	( __GFP_WAIT | __GFP_IO)
	 * GFP_KERNEL	( __GFP_WAIT | __GFP_IO | __GFP_FS )
	 * GFP_USER	( __GFP_WAIT | __GFP_IO | __GFP_FS )
	 * GFP_HIGHUSER ( __GFP_WAIT | __GFP_IO | __GFP_FS | __GFP_HIGHMEM )
	 * GFP_DMA	( __GFP_DMA )
	 */

	/*
	 * Which flag to use ?
	 *
	 * GFP_KERNEL process context and can sleep
	 * GFP_ATOMIC process context and can't sleep
	 * GFP_ATOMIC Interrupt handler/tasklets/softirq's
	 * GFP_KERNEL | GFP_DMA Need DMA'ble memory and can sleep
	 * GFP_ATOMIC | GFP_DMA Need DMA'ble memory and can't sleep.
	 */

	/*
	 * Address returned by Kmalloc will be physically
	 * contigious.
	 * @max memory that can be allocated is defined by MAX_ORDER
	 * and PAGE_SHIFT it is arch dependent.
	 * #define KMALLOC_SHIFT_HIGH ((MAX_ORDER + PAGE_SHIFT - 1) <= 25
	 *
	 */

	/*
	 * ZERO_SIZE_PTR will be returned for zero sized kmalloc requests.
	 *
	 * Dereferencing ZERO_SIZE_PTR will lead to a distinct access fault.
	 *
	 * ZERO_SIZE_PTR can be passed to kfree though in the same way that NULL can.
	 * Both make kfree a no-op.
	 */

	/*
	 * Address returned by Kmalloc is cacheable. Device drivers must take
	 * care of flush and invalidation of caches.
	 */


	buff = kmalloc(BUFF_SIZE, GFP_ATOMIC);
	if (!buff) {
		printk("Memory allocation failed\n");
		return -ENOMEM;
	}
	printk("Memory allocated.... %ld\n", ksize(buff));
	return 0;
}

static void __exit memory_exit(void)
{
	if (buff)
		kfree(buff);

	printk("Memory De-allocated....\n");
}

module_init(memory_init);
module_exit(memory_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("WebEm");

