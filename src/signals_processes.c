/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_processes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 22:53:56 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/10 11:16:17 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echoctl(bool status)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	if (status)
		term.c_lflag |= ECHOCTL;
	else
		term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 1;
	}
}

void	sig_handler_child(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		g_exit_status = 130;
	}
	if (signum == SIGQUIT)
	{
		printf("Quit: %d\n", SIGQUIT);
		g_exit_status = 131;
	}
}

void	signals_for_parent(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_for_child(void)
{
	signal(SIGINT, sig_handler_child);
	signal(SIGQUIT, sig_handler_child);
}
