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
# include <termios.h>
# include <dirent.h>
# include "libft/libft.h"
# include "string.h"

// ANSI color escape codes
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct mini_s
{
    char *cmd;
    char **args;
    char *path;
}mini_t;

#endif