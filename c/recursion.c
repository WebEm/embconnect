
// SPDX-License-Identifier: GPL-2.0+
/*
 * 2020+ Copyright (c) WebEm <embconnect001@gmail.com>
 * All rights reserved.
 */

#include <stdio.h>
/*
 * The recursion will exploit stack. every time the function is called
 * activation record is created called ascending phase and when the condition 
 * fails it enters in to descending phase of the stack
 *
 *  In the given example func is invoked three times.
 *  acscendig phase
 *  --------
 *  | x = 3|
 *  --------
 *  | x = 2|
 *  --------
 *  | x = 1|
 *  --------
 *  descending phase
 *  --------
 *  | x = 1|
 *  --------
 *  | x = 2|
 *  --------
 *  | x = 3|
 *  --------
 */
void func(int x)
{
	if (x > 0) {
		printf("the value of n %d\n", x);
		func(x - 1);
		printf("the value of n %d\n", x);
	}
}

int main(int argv, char *argc[])
{
	int y = 3;
	func(3);
}
