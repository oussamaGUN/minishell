#include "../main.h"

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
t_env *envir(char **envp)
{
	int		i;
	char	**arr;
	t_env	*env;
	t_env	*node;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		node = malloc(sizeof(t_env));
		node->next = NULL;
		arr = ft_split(envp[i], '=');
		if (!arr)
			return NULL;
		node->key = ft_strdup(arr[0]);
		if (ft_strncmp(node->key, "SHLVL", 6) == 0)
			node->value = ft_strdup("2");
		else
			node->value = ft_strdup(arr[1]);
		list_for_env(&env, node);
		i++;
	}
	return env;
}