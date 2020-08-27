// SPDX-License-Identifier: GPL-2.0+
/*
 * 2020+ Copyright (c) WebEm <embconnect001@gmail.com>
 * All rights reserved.
 */

/*
 * code to list files in the given directory.
 */

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#define MAX_ARG	2

int main(int argv, char *argc[])
{
	DIR *dp;
	struct dirent *dirp;

	if (argv != MAX_ARG) {
		printf("Enter directory to display contents\n");
		return 0;
	}

	dp = opendir(argc[1]);
	if (dp == NULL) {
		switch (errno) {
		case ENOTDIR:
		case EBADF:
		case EACCES:
		case EMFILE:
		case ENOENT:
		case ENOMEM:
			printf("Error %s\n", strerror(errno));
			break;
		default:
			printf("Error in opening a dir\n");
			return -1;
		}
	}
	while (dirp = readdir(dp)) {
		/* exclude . and .. */
		if ((strcmp(dirp->d_name, ".") == 0) ||
		    (strcmp(dirp->d_name, "..") == 0))
			continue;

		printf("Filename: %s\n", dirp->d_name);
	}
	closedir(dp);
	return 0;
}

