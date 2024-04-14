#include "../main.h"

char *ft_env(t_env *env, char *s)
{
    t_env *lst = env;
    while (lst)
    {
        if (ft_strncmp(lst->key, s, ft_strlen(s)) == 0)
            return lst->value;
        lst = lst->next;
    }
    return NULL;
}
int pwd(t_token *lst, t_env *env)
{
    char buff[4096];
	char *path;
	path = getcwd(buff, 4096);
    if (!path)
    {
        printf("bash: No such file or directory\n");
        return 0;
    }
    else
    {
	    lst->path = ft_strdup(path);
        printf("%s\n", lst->path);
    }
    return 1;
}
int cd(char **arr, t_env *env)
{
    if (!arr[1])
    {
        if (chdir(ft_env(env, "HOME")) == -1)
        {
            perror("bash");
            return 0;
        }
    }
    else if (chdir(arr[1]) == -1)
    {
        perror("bash");
        return 0;
    }
    return 1;
}
t_env *ft_update_pwd_env(t_env *env)
{
	char buff[4096];
	char *path;
	path = getcwd(buff, 4096);
    if (!path)
        return env;
	t_env *itter = env;
	while (itter)
	{
		if (ft_strncmp(itter->key, "PWD", 4) == 0)
			itter->value = ft_strdup(path);
		itter = itter->next;
	}
	return env;
}
t_env *ft_update_oldpwd_env(t_env *env)
{
	char buff[4096];
	char *path;
	path = getcwd(buff, 4096);
    if (!path)
        return env;
	t_env *itter = env;
	while (itter)
	{
		if (ft_strncmp(itter->key, "OLDPWD", 7) == 0)
			itter->value = ft_strdup(path);
		itter = itter->next;
	}
	return env;
}
int env_print(t_env *env)
{
    t_env *itter = env;
    while (itter)
    {
        printf("%s=%s\n", itter->key, itter->value);
        itter = itter->next;
    }
    return 1;
}
int ft_dashn(char *s)
{
    int i;

    i = 0;
    if (s[i] == '-')
        i++;
    else
        return 0;
    while (s[i])
    {
        if (s[i] != 'n')
            return 0;
        i++;
    }
    return 1;
}
int echo(t_token *lst)
{
    int i;
    if (!lst->arr[1])
        printf("\n");
    else if (ft_dashn(lst->arr[1]))
    {
        i = 2;
        while (lst->arr[i])
            ft_putstr_fd(lst->arr[i++], 1);
    }
    else
    {
        i = 1;
        while (lst->arr[i])
        {
            ft_putstr_fd(lst->arr[i], 1);
            i++;
            if (lst->arr[i])
                ft_putstr_fd(" ", 1);
        }
        ft_putstr_fd("\n", 1);
    }
    return 1;
}
int builtins(t_token *lst, t_env *env)
{
    if (ft_strncmp(lst->arr[0], "cd", 3) == 0 || ft_strncmp(lst->arr[0], "CD", 3) == 0)
    {
        env = ft_update_oldpwd_env(env);
        if (!cd(lst->arr, env))
            return 0;
    }
    else if (ft_strncmp(lst->arr[0], "pwd", 3) == 0 || ft_strncmp(lst->arr[0], "PWD", 3) == 0)
    {
        if (!pwd(lst, env))
            return 0;
    }
    else if (ft_strncmp(lst->arr[0], "env", 4) == 0)
    {
	    env = ft_update_pwd_env(env);
        if (!env_print(env))
            return 0;
    }
    else if (ft_strncmp(lst->arr[0], "echo", 5) == 0 || ft_strncmp(lst->arr[0], "echo", 5) == 0)
    {
        if (!echo(lst))
            return 0;
    }
    return 1;
}