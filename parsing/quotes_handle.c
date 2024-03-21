#include "../main.h"

int quotes_compare(char **arr)
{
    int len = 0;
    while (arr[len])
        len++;
    int i = 0;
    int mid = len - 1;

    while (i <= mid / 2)
    {
        if (strcmp(arr[i], arr[mid]))
            return 0;
        i++;
        mid--;
    }
    return 1;

}
int check_node(char *s)
{
    int i = 0;
    int len = 0;
    char **arr;
    while (s[i])
    {
        if (s[i] == '\'' || s[i] == '\"')
            len++;
        i++;
    }
    if (len == 0)
        return 2;
    arr = malloc(sizeof(char *) * (len + 1));
    i = 0;
    int j = 0;
    while (s[i])
    {
        if (s[i] == '\'' || s[i] == '\"')
        {
            arr[j] = malloc(sizeof(char) * (2));
            arr[j][0] = s[i];
            arr[j][1] = '\0';
            j++;
        }
        i++;
    }
    arr[j] = NULL;
    if (!quotes_compare(arr))
        return 0;
    return 1;
}
int nested_quotes(t_token *token)
{
    t_token *ptr;

    ptr = token;
    while (ptr)
    {
        if (!check_node(ptr->content))
            return 0;
        ptr = ptr->next;
    }
    return 1;
}
t_token *ft_pars(t_token *token)
{
    if (!nested_quotes(token))
    {
        ft_putendl_fd("nested quotes", 2);
        return token;
    }
    if (!syntax_error(token))
    {
        ft_putendl_fd("syntax error", 2);
    }
    return token;
}