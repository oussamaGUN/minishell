#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <termios.h>
# include <dirent.h>
# include "libft/libft.h"
# include <string.h>

// ANSI color escape codes
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct mini_s
{
    char *cmd;
    char **args;
    char *path;
    int input;
    int fd[2];
    int flag_for_file_output;
    int flag_for_file_input;
    int file_mulipipes;
    char **piped_command;
    int pid;
}mini_t;

void normal_cmd(mini_t *mini, char **env);
char *ft_getpath(char *cmd, char **env);
void exec_first_cmd(mini_t *mini, char *cmd,char **env);
void ft_input_execution(mini_t *mini, char **env, char *cmd);
void ft_output_execution(mini_t *mini, char **env, char *cmd);
void	signals_handle(void);
#endif