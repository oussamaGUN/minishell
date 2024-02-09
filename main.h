#ifndef MAIN_H
# define MAIN_H

# include "libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <termios.h>

// ANSI color escape codes
# define ANSI_COLOR_YELLOW "\x1b[33m"
# define ANSI_COLOR_RESET "\x1b[0m"
typedef struct mini_s
{
	char	*cmd;
	char	**args;
	char	*path;
	int		input;
	int		fd[2];
	char	**piped_command;
	int		pid;
}			mini_t;

void		normal_cmd(mini_t *mini, char **env);
char		*ft_getpath(char *cmd, char **env);
void		exec_first_cmd(mini_t *mini, char *cmd, char **env);
void		ft_input_execution(mini_t *mini, char **env, char *cmd);
void		ft_output_execution(mini_t *mini, char **env, char *cmd);
void		signals_handle(void);
void		check_builtin(mini_t *mini, char **env, int exit_status);
void		ft_cd(mini_t *mini, char **env);
void		ft_echo(mini_t *mini, char **env, int exit_status);
#endif