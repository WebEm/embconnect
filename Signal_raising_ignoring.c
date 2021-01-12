#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
void handler_sigtstp(int signum);
int main()
{
void (*sigHandlerReturn)(int);
sigHandlerReturn=signal(SIGTSTP,SIG_IGN);
if(sigHandlerReturn==SIG_ERR)
{
perror("signal error:");
return 1;
}
printf("testing SIGTSTP\n");
raise(SIGTSTP);
printf("signal is ignored\n");
return 0;
}


