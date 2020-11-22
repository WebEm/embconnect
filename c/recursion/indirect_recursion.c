
// SPDX-License-Identifier: GPL-2.0+
/*
 * 2020+ Copyright (c) WebEm <embconnect001@gmail.com>
 * All rights reserved.
 */

#include <stdio.h>

void funcb(int x);

void func(int a)
{
	if (a > 0 ) {
		printf ("Val of a is %d\n", a);
		funcb(a -1);
	}
}

void funcb(int x)
{
	if (x > 1) {
		printf("val of x is %d\n", x);
		func(x / 2);
	}
}

int main(int argv, char *argc[])
{
	func(20);
}
