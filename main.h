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
# include <sys/stat.h>

// ANSI color escape codes
# define ANSI_COLOR_YELLOW "\x1b[33m"
# define ANSI_COLOR_RESET "\x1b[0m"


// tokenize
int exit_status;
typedef struct s_token
{
	int type;
	char *content;
	char **arr;
	int output_file;
	int input_file;
	int fd[2];
	int exit_status;
	char *path;
	struct s_token *next;
	struct s_token *prev;
	pid_t pid;
}	t_token;

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}t_env;


typedef struct s_tokenizer
{
	size_t			words_count;
	size_t word_len;
	char			**arr;
	int flag;
	int i;
	int j;
	int k;
	char const *s;
	char *res;
	int count1;
	int count2;
}t_tokenizer;


typedef struct s_multx
{
    char *normal;
    char *inside_dquotes;
    char *inside_squotes;
    char *cpy;
    char *exp;
    char *res;
	int i;
    int k;
    int j;
	int count;
}t_multx;

typedef enum e_type {
	WORD,
	PIPE,
	RED_OUTPUT,
	RED_INPUT,
	RED_APPEND,
	HERE_DOC,
	FILE_APP,
	FILE_OUT,
	FILE_IN,
	DELIMITER,
}t_type;





// list 
t_token	*new(void *content);
void	ft_lstadd(t_token **lst, t_token *new);
int	lstsize(t_token *lst);
// parsing





void	clear(t_token **lst, void (*del)(void *));
void del(void *s);

// void		ft_quit(int sig);
// t_list		*ft_lst_creat_env(mini_t *mini, char **env);



int tokenizer(char *str, t_token **token);
char	**ft_ownsplit(char const *s, char c, t_tokenizer *vars);
t_token *ft_check_errors(t_token *token);
int syntax_error(t_token *token);
t_token *ft_list(t_token *token, t_env *env);
t_token *expanding(t_token *token, t_env *env);
int here_doc(t_token *token);
char *expand(char *s, t_env *envp);

// execution
char	*ft_getpath(char *cmd, char **env);
int execution(t_token *lst, t_env *env);
int builtins(t_token *lst, t_env *env);
char *ft_env(t_env *env, char *s);


//env
t_env *envir(char **envp);
void	list_for_env(t_env **lst, t_env *new);
#endif