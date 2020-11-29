
// SPDX-License-Identifier: GPL-2.0+
/*
 * 2020+ Copyright (c) WebEm <embconnect001@gmail.com>
 * All rights reserved.
 */

#include <stdio.h>

void func(int x)
{
	if (x > 0) {
		printf("val of x is %d\n", x);
		func(x-1);
		func(x-1);
	}
}

int main(int argv, char *argc[])
{
	func(3);
}
