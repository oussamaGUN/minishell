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


// tokenize
typedef struct s_token
{
	int type;
	char *content;
	struct s_token *next;
}	t_token;

typedef enum s_type {
	WORD,
	PIPE,
	RED_OUTPUT,
	RED_INPUT,
	RED_APPEND,
	HER_DOC,
	FILE_APP,
	FILE_OUT,
	FILE_IN,
}t_type;

void tokenizer(char *str, t_token **token);
char	**ft_ownsplit(char const *s, char c);



//parsing
typedef struct s_parsing
{
	t_token *pars;
}t_parsing;
t_token *ft_pars(t_token *token);
// parsing


// execution
typedef struct mini_s
{
	char	*cmd;
	char	**args;
	char	*path;
	int		input;
	int		fd[2];
	char	**piped_command;
	int		pid;
	char	current_path[1024];
}			mini_t;


void	clear(t_token **lst, void (*del)(void *));
void del(void *s);
void		normal_cmd(mini_t *mini, char **env);
char		*ft_getpath(char *cmd, char **env);
void		exec_first_cmd(mini_t *mini, char *cmd, char **env);
void		ft_input_execution(mini_t *mini, char **env, char *cmd);
void		ft_output_execution(mini_t *mini, char **env, char *cmd);
void		signals_handle(void);
void		check_builtin(mini_t *mini, char **env);
void		ft_cd(mini_t *mini, char **env);
void		handler(int signal_num);
void		ft_quit(int sig);
void		handle_process(int signal_num);
void		ft_pwd(mini_t *mini, char **env);
void		ft_export(mini_t *mini, char **env);
char		**ft_split_env(char *str, char **env);
// t_list		*ft_lst_creat_env(mini_t *mini, char **env);


#endif