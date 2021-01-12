#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>
#include<sys/types.h>


int main(int argv,char *argc[])
{

DIR*p;
struct dirent *d;

if (argv != 2) {
		printf("Enter directory to display contents\n");
		return 0;
	}

p=opendir(argc[1]);
if(p==NULL)
  {
  perror("Cannot find directory");
  exit(-1);
  }
while(d=readdir(p))
  printf("%s\n",d->d_name);
  closedir(p);
  return 0;
}
