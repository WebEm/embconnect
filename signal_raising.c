#include<stdio.h>
#include<signal.h>
#include<stdio.h>
int main()
{
printf("testing sigstop\n");
printf("before raising signal\n");
raise(SIGSTOP);
printf("after raising signal\n");
return 0;
}
