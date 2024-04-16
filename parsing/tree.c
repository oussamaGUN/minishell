#include "../main.h"

int ft_words(t_token *token)
{
    int count = 0;
    t_token *itter = token;
    while (itter && itter->type != PIPE)
    {
        if (itter->type == WORD)
            count++;
        itter = itter->next;
    }
    return count;
}
void here_doc_expand_norm(t_multx *vars, char *s, t_env *env)
{
    vars->i++;
    while (s[vars->i] != ' '
        && s[vars->i] && ft_isalnum(s[vars->i]))
    {
        vars->inside_dquotes[vars->j] = s[vars->i];
        vars->i++;
        vars->j++;
    }
    vars->inside_dquotes[vars->j] = '\0';
    vars->exp = expand(vars->inside_dquotes, env);
    if (vars->exp)
    {
        vars->res = ft_malloc(0, &(env->mem),
                    ft_strjoin(vars->res, vars->exp));
        vars->k = ft_strlen(vars->res);
    }
    else
        vars->res = ft_malloc(0, &(env->mem), ft_strjoin(vars->res, ""));
    vars->i--;
}
void here_doc_expand_norm_two(t_multx *vars, char *s, t_env *env)
{
    if (s[vars->i] == '$' && ft_isdigit(s[vars->i + 1]))
        vars->i++;
    else
        vars->res = ft_malloc(0 ,&(env->mem) ,
                    ft_strjoin(vars->res, &s[vars->i]));
}
char *here_doc_expand(char *s, t_env *env)
{
    t_multx *vars;
    
    vars = ft_malloc(sizeof(t_multx), &(env->mem), NULL);
    vars->inside_dquotes = ft_malloc(ft_strlen(s), &(env->mem), NULL);
    vars->res = ft_malloc(ft_strlen(s), &(env->mem), NULL);
    if (!vars || !vars->inside_dquotes || !vars->res)
        return (NULL);
    vars->res[0] = '\0';
    vars->k = 0;
    vars->i = 0;
    while (s[vars->i])
    {
        vars->j = 0;
        if (s[vars->i] == '$' && s[vars->i + 1] != ' '
        && s[vars->i + 1] && !ft_isdigit(s[vars->i + 1]))
            here_doc_expand_norm(vars, s, env);
        else
            here_doc_expand_norm_two(vars, s, env);
        if (vars->res[vars->k])
            vars->k++;
        if (s[vars->i])
            vars->i++;
        vars->res[vars->k] = '\0';
    }
    return vars->res;
}
int ft_here_doc_count(t_token *token)
{
    t_token *n = token;
    int count = 0;
    while (n)
    {
        if (n->type == DELIMITER)
            count++;
        n = n->next;
    }
    if (count > 16)
        return 0;
    count = 1;
    return count;
}
t_token *child_process_for_heredoc(t_token *token, t_token *node, t_env *env, int file)
{
    while (1)
    {
        char *s = readline("> ");
        if (!s)
            break;
        if (ft_strncmp(s, "\n", ft_strlen(s)) == 1 
            && ft_strncmp(s, token->content, ft_strlen(token->content)) == 0 )
            break ;
        char *new = here_doc_expand(s, env);
        if (!new)
            return NULL;
        ft_putendl_fd(new, file);
    }
    close(token->fd[1]);
    exit(0);
}
int here_doc_mininorm(t_token *token)
{
    if (!ft_here_doc_count(token))
    {
        perror("bash: maximum here-document count exceeded");
        return -1;
    }
    if (pipe(token->fd) == -1)
        return -1;
    return token->fd[1];
}
t_token *here_doc_implement(t_token *token, t_token *node, t_env *env)
{
    int file;
    pid_t id;

    file = here_doc_mininorm(token);
    if (file < 0)
        return NULL;
    id = fork();
    if (id == -1)
        return NULL;
    else if (id == 0)
        child_process_for_heredoc(token, node, env, file);
    close(token->fd[1]);
    wait(NULL);
    node->input_file = token->fd[0];
    if (node->input_file == -1)
    {
        printf("bash: %s: No such file or directory\n", token->content);
        return NULL;
    }
    return token;
}
t_token *ft_openning_files(t_token *token, t_token *node)
{
    if (token->type == FILE_OUT)
    {
        node->output_file = open(token->content,  O_TRUNC | O_CREAT | O_WRONLY, 0644);
        if (node->output_file == -1)
            return NULL;
    }
    else if (token->type == FILE_IN)
    {
        node->input_file = open(token->content, O_RDONLY);
        if (node->input_file == -1)
        {
            printf("bash: %s: No such file or directory\n", token->content);
            return NULL;
        }
    }
    else if (token->type == FILE_APP)
    {
        node->output_file = open(token->content,  O_APPEND | O_CREAT | O_WRONLY, 0644);
        if (node->output_file == -1)
            return NULL;
    }
    return token;
}
t_token *little_norm(t_token *node, t_multx *vars, t_token *token, t_free **mem)
{
    vars->count = ft_words(token);
    vars->i = 0;
    node->arr = ft_malloc(sizeof(char *) * (vars->count + 1), mem, NULL);
    if (!node->arr)
        return NULL;
    node->output_file = -1;
    node->input_file = -1;
    return node;
}
t_token *normy(t_token *token, t_env *env, t_token *node, t_multx *vars)
{
    if (token->type == WORD)
        node->arr[vars->i++] = ft_malloc(0, &(env->mem),
                                ft_strdup(token->content));
    else if (!ft_openning_files(token, node))
        return (NULL);
    else if (token->type == DELIMITER)
    {
        if (!here_doc_implement(token, node, env))
            return (NULL);
    }
    return token;
}
void free_node(t_token *node)
{
    int i;

    i = 0;
    while (node->arr[i])
        free(node->arr[i++]);
    free(node->arr);
    free(node->content);
    free(node);
}
t_token *ft_list(t_token *token, t_env *env)
{
    t_token *lst;
    t_token *node;
    t_multx *vars;

    vars = ft_malloc(sizeof(t_multx), &(env->mem), NULL);
    if (!vars)
        return (NULL);
    lst = NULL;
    while (token)
    {
        node = add_token(token->content, &(env->mem));
        if (!little_norm(node, vars, token, &(env->mem)))
            return (NULL);
        while (token && token->type != PIPE)
        {
            if (!normy(token, env, node, vars))
                return (NULL);
            token = token->next;
        }
        node->arr[vars->i] = NULL;
        ft_lstadd(&lst, node);
        if (token)
            token = token->next;
    }
    return lst;
}
