#ifndef MAIN_H
# define MAIN_H

# include "libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <termios.h>
# include <sys/stat.h>
# include <errno.h>


# define READLINE_LIBRARY
# include "history.h"
# include "readline.h"


// tokenize
int exit_status;
typedef struct s_token
{
	int	type;
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

typedef	struct s_free
{
	void			*mem;
	struct s_free	*next;
}					t_free;

typedef struct s_env
{
	char			*key;
	char			*value;
	char			**envp;
	struct s_free	*mem;
	struct s_env	*next;
}t_env;


typedef struct s_tokenizer
{
	size_t		words_count;
	size_t		word_len;
	char		**arr;
	int 		flag;
	int			i;
	int			j;
	int			k;
	char const	*s;
	char 		*res;
	int 		count1;
	int 		count2;
}				t_tokenizer;


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
	CMD,
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
t_token	*add_token(void *content, t_free **alloc);
void	ft_lstadd(t_token **lst, t_token *new);
int	lstsize(t_token *lst);
// parsing





void	clear(t_token **lst, void (*del)(void *));
void del(void *s);

// void		ft_quit(int sig);
// t_list		*ft_lst_creat_env(mini_t *mini, char **env);



int tokenizer(char *str, t_token **token, t_env **env);
char	**ft_ownsplit(char const *s, char c, t_tokenizer *vars);
t_token *ft_check_errors(t_token *token);
int syntax_error(t_token *token);
t_token *ft_list(t_token *token, t_env *env);
t_token *expanding(t_token *token, t_env *env);
// int here_doc(t_token *token);
char *expand(char *s, t_env *envp);
int	pipe_error(t_token *s);
int	red_output_error(t_token *s);
int	red_input_error(t_token *s);
int	red_append_error(t_token *s);
void	ft_expanding_the_inside(t_multx *exp_vars, char *s, t_env *env);
void	ft_double_quotes_expand(t_multx *exp_vars, char *s, t_env *env);
void	ft_single_quotes(t_multx *exp_vars, char *s, t_env *env);
void	ft_expand_normalin_multi(t_multx *exp_vars, char *s, t_env *env);
void	ft_expand_single_in_multiple(t_multx *exp_vars, char *s, t_env *env);
void	ft_exit_value(t_multx *exp_vars, char *s, t_env *env);
void	ft_delemiter(t_multx *exp_vars, char *s, t_free **mem);
char	*expand(char *s, t_env *envp);
t_token	*norm1(t_token *node, t_multx *vars, t_token *token, t_free **mem);
t_token	*norm2(t_token *token, t_env *env, t_token *node, t_multx *vars);
t_token	*ft_openning_files(t_token *token, t_token *node);
int	ft_words(t_token *token);
t_token	*here_doc_implement(t_token *token, t_token *node, t_env *env);
void	here_doc_expand_norm(t_multx *vars, char *s, t_env *env);
void	here_doc_expand_norm_two(t_multx *vars, char *s, t_env *env);
// execution
char	*ft_getpath(char *cmd, char **env);
int exec(t_token *lst, t_env *env);
int execution(t_token *lst, t_env *env);
int builtins(t_token *lst, t_env *env);
char *ft_env(t_env *env, char *s);


//env
t_env *envir(char **envp);
void	list_for_env(t_env **lst, t_env *new);
t_env *ft_update_pwd_env(t_env *env);
void	env_clear(t_env **env);

// garbage collector
void	*ft_malloc(size_t	size, t_free **alloc, void *mem);
void	garbage_collector(t_free **alloc);
void	add_front_mem(t_free **alloc, t_free *new);

#endif
