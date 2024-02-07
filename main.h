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
#define ANSI_COLOR_GREEN   "\x1b[32m"
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
    int file_input;
    int j;
}mini_t;

void ft_handle_redirection(mini_t *mini, char **env);
void normal_cmd(mini_t *mini, char **env);
char *ft_getpath(char *cmd, char **env);
void signals_handle(char *cmd);
void ft_redirect_file(mini_t *mini, char **env);
void exec_first_cmd(mini_t *mini, char *cmd,char **env);
void ft_input_execution(mini_t *mini, char **env, char *cmd);
void ft_output_execution(mini_t *mini, char **env, char *cmd);
void ft_inputfilefor_multipipes(mini_t *mini, char **env);
void ft_redirect_file_append(mini_t *mini, char **env);
#endif