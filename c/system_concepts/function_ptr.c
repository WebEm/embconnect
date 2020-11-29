/*
 *   function_ptr.c
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
 * Simple program to explain function pointers.
 * structure with function pointers.
 * function gets assigned to function pointers and 
 * will be invoked in the code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

struct fptr {
	void (*ptr) (void); /* func pointer takes no args */
	/* func pointer taking int as arg and returns an int */
	int (*ptr1) (int);  
	/* func pointer taking int as arg and rturns int* */
	int* (*ptr2) (int);
};

void func (void)
{
	printf("invoking function pointer with no arg\n");
}

int func1 (int a)
{
	printf("invoking function pointer taking int as arg val:%d\n", a);
	return 0;
}

int* func2 (int a)
{
	
	printf("invoking function pointer returning val:%d\n", a);
}

int main(int argv, char*argc[])
{
	struct fptr *func_ptr;
	
	func_ptr = (struct fptr *)malloc(sizeof(struct fptr));
	if (!func_ptr) {
		printf("No mem\n");
		return -ENOMEM;
	}

	func_ptr->ptr = func;
	func_ptr->ptr1 = func1;
	func_ptr->ptr2 = func2;

	if (func_ptr->ptr)
		func_ptr->ptr();
	if (func_ptr->ptr1)
		func_ptr->ptr1(10);

	return 0;
}
