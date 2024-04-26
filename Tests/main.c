#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>



void sig_handler(int signum)
{
	if (signum == SIGCHLD)
	{
		printf("Child process has been terminated\n");
	}
	if (signum == SIGQUIT)
		exit(0);
}

int main()
{
	signal(SIGCHLD, sig_handler);
	if (fork())
		sleep(10);
}

