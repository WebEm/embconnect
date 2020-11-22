
// SPDX-License-Identifier: GPL-2.0+
/*
 * 2020+ Copyright (c) WebEm <embconnect001@gmail.com>
 * All rights reserved.
 */
#include <stdio.h>

int func(int n)
{
	if (n > 100) {
		return (n - 10);
	} else { 
		return func(func(n + 11));
	}
}

void main(int argv, char *argc[])
{
	int result;
	result = func(95);

	printf("Val of result: %d\n", result);
}
