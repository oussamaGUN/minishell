#include "main.h"

void sig_handler_for_heredoc()
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	exit(1);
}
void signal_for_heredoc()
{
	signal(SIGINT, sig_handler_for_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit_status = 1;
	}
	if (signum == SIGQUIT)
	{
		printf("Quit: %d\n", SIGQUIT);
		exit(131);
	}
}

void signals_for_parent()
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
void signals_for_child()
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT,sig_handler);
}
