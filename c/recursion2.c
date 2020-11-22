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
 *  | x = 4| + x
 *  --------
 *  | x = 3| + x
 *  --------
 *  | x = 2| + x
 *  --------
 *  | x = 1| + x
 *  --------
 *  | x = 0| + x 
 *  --------
 *  descending phase
 *  --------
 *  | x = 0|  0 + 1 = 1
 *  --------
 *  | x = 1|  1 + 2 = 3  (val of x = 2)
 *  --------
 *  | x = 2|  3 + 3 = 6  (val of x = 3)
 *  --------
 *  | x = 3|  6 + 4 = 10 (val of x = 4)
 *  --------
 *  | x = 4| 10 + 5 = 15 (val of x = 5)
 *  --------
 */
int func(int x)
{
	if (x > 0) {
		return func(x-1) + x;
	}
	return 0;
}

int main(int argv, char *argc[])
{
	printf("%d\n", func(5));
}
