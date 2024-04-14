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

char *here_doc_expand(char *s, t_env *env)
{
    int i = 0;
    int j = 0;
    char *inside_dquotes = malloc(ft_strlen(s));
    char *res = malloc(ft_strlen(s) * 1);
    res[0] = '\0';
    int k = 0;
    char *exp;
    while (s[i])
    {
        j = 0;
        if (s[i] == '$' && s[i + 1] != ' ' && s[i + 1] && !ft_isdigit(s[i + 1]))
        {
            i++;
            while (s[i] != ' ' && s[i] && ft_isalnum(s[i]))
            {
                inside_dquotes[j] = s[i];
                i++;
                j++;
            }
            inside_dquotes[j] = '\0';
            exp = expand(inside_dquotes, env);

            if (exp)
            {
                res = ft_strjoin(res, exp);
                k = ft_strlen(res);
            }
            else
                res = ft_strjoin(res, "");
            i--;
        }
        else
        {
            if (s[i] == '$' && ft_isdigit(s[i + 1]))
                i++;
            else
            {
                res = ft_strjoin(res, &s[i]);
            }
        }
        if (res[k])
            k++;
        if (s[i])
            i++;
        res[k] = '\0';
        // printf("%c\n", s[i]);
    }
    return res;
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
t_token *ft_list(t_token *token, t_env *env)
{
    t_token *lst = NULL;
    t_token *node;
    int count = 0;
    int i = 0;
    if (!ft_here_doc_count(token))
    {
        perror("bash: maximum here-document count exceeded");
        return NULL;
    }
    while (token)
    {
        node = new(token->content);
        count = ft_words(token);
        node->arr = malloc(sizeof(char *) * (count + 1));
        node->output_file = -1;
        node->input_file = -1;
        i = 0;
        while (token->type != PIPE)
        {
            if (token->type == WORD)
                node->arr[i++] = ft_strdup(token->content);
            else if (token->type == FILE_OUT)
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
            else if (token->type == DELIMITER)
            {
                if (pipe(token->fd) == -1)
                    return NULL;
                int file = token->fd[1];
                if (file == -1)
                {
                    printf("bash: %s: No such file or directory\n", token->content);
                    return NULL;
                }
                pid_t id = fork();
                if (id == -1)
                    return NULL;
                else if (id == 0)
                {
                    while (1)
                    {
                        char *s = readline("> ");
                        if (!s)
                            break;
                        if (ft_strncmp(s, "\n", ft_strlen(s)) == 1 && ft_strncmp(s, token->content, ft_strlen(s)) == 0 )
                        {
                            break ;
                        }
                        char *new = here_doc_expand(s, env);
                        if (!new)
                            return NULL;
                        ft_putendl_fd(new, file);
                    }
                    close(token->fd[1]);
                    exit(0);
                }
                close(token->fd[1]);
                    wait(NULL);
                node->input_file = token->fd[0];
                if (node->input_file == -1)
                {
                    printf("bash: %s: No such file or directory\n", token->content);
                    return NULL;
                }
            }
            token = token->next;
            if (!token)
                break;
        }
        node->arr[i] = NULL;
        ft_lstadd(&lst, node);
        if (token)
            token = token->next;
    }
    return lst;
}
