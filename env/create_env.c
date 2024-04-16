#include "../main.h"

void	env_clear(t_env **env)
{
	if (*env)
	{
		free((*env)->key);
		free((*env)->value);
		free(*env);
		(*env) = (*env)->next;
	}
}

void	list_for_env(t_env **lst, t_env *new)
{
	t_env	*ptr;

	if (lst && *lst)
	{
		ptr = *lst;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	else if (lst)
		*lst = new;
}
void ft_free_env(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
t_env	*envir(char	**envp)
{
	int		i;
	char	**arr;
	t_env	*env;
	t_env	*node;

	i = -1;
	env = NULL;
	while (envp[++i])
	{
		arr = ft_split(envp[i], '=');
		if (!arr)
			return (NULL);
		node = malloc(sizeof(t_env));
		if (!node)
			return (NULL);
		node->next = NULL;
		node->key = ft_strdup(arr[0]);
		if (ft_strncmp(node->key, "SHLVL", 6) == 0)
			node->value = ft_strdup("2");
		else
			node->value = ft_strdup(arr[1]);
		ft_free_env(arr);
		list_for_env(&env, node);
	}
	return (env);
}
