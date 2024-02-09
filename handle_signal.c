#include "main.h"

void	handler(int signal_num)
{
	write(1, "\n" ANSI_COLOR_YELLOW "→" ANSI_COLOR_RESET " ", 14);
	return ;
}
void	signals_handle(void)
{
	if (signal(SIGINT, handler) == SIG_ERR)
	{
		perror("signal");
		return ;
	}
    if (signal(SIGQUIT, SIG_IGN) == SIG_ERR) {
        perror("signal");
        exit(EXIT_FAILURE);
    }
}