/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:43:56 by ousabbar          #+#    #+#             */
/*   Updated: 2024/04/22 16:30:49 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	exit_status = 1 << 8;
}

void sig_quit(int signum)
{
	printf("Quit: %d\n", signum);
	rl_on_new_line();
	rl_replace_line("", 0);
	exit_status = 131 << 8;
}

void	sig_handler_for_process(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	exit_status = 131 << 8;
}

void signals_for_parent()
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
void signals_for_child()
{
	signal(SIGINT, sig_handler_for_process);
	signal(SIGQUIT, sig_quit);
}