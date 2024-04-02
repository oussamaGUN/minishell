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
t_token *ft_list(t_token *token)
{
    t_token *lst = NULL;
    t_token *node;
    int count = 0;
    int i = 0;
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
                int file = open(".heredoc_tmp", O_TRUNC | O_CREAT | O_WRONLY, 0644);
                if (file == -1)
                {
                    printf("bash: %s: No such file or directory\n", token->content);
                    return NULL;
                }
                while (1)
                {
                    char *s = readline("> ");
                    if (ft_strncmp(s, "\n", ft_strlen(s)) == 1)
                    {
                        if (ft_strncmp(s, token->content, ft_strlen(s)) == 0 )
                        {
                            break ;
                        }
                    }
                    ft_putendl_fd(s, file);
                }
                node->input_file = open(".heredoc_tmp", O_RDONLY);
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
