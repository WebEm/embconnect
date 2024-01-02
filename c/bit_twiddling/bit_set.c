// SPDX-License-Identifier: GPL-2.0+
/*
 * 2024+ Copyright (c) WebEm <embconnect001@gmail.com>
 * All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
int countsetbits(unsigned int n) {
    int count = 0;
    while (n) {
        n &= (n - 1);
	printf ("value of n :%d\n", n);
        count++;
    }
    return count;
}

int main(int argc, char *argv[])
{
	int num;
	printf("Enter the numbet to find the no_of_bit_set:");
	scanf("%d", &num);
	printf("total bit set in %d: %d\n", num, countsetbits(num));

	return 0;
}
