#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
void handler_sigtstp(int signum);
int main()
{
void (*sigHandlerReturn)(int);
sigHandlerReturn=signal(SIGTSTP,handler_sigtstp);
if(sigHandlerReturn==SIG_ERR)
{
perror("signal error:");
return 1;
}
printf("testing SIGTSTP\n");
raise(SIGTSTP);
return 0;
}

void handler_sigtstp(int signum)
{
if(signum==SIGTSTP)
{
printf("receive sigstp\n");
exit(0);
}

else
printf("received %d signal \n",signum);
return;
}
