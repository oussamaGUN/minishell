/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 21:14:05 by ousabbar          #+#    #+#             */
/*   Updated: 2024/04/22 19:52:40 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "main.h"

void	env_clear(t_env **env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = *env;
		*env = (*env)->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
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
	{
		*lst = new;
	}
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
			return (ft_free_env(arr), NULL);
		node->next = NULL;
		node->key = ft_strdup(arr[0]);
		if (ft_strncmp(node->key, "SHLVL", 6) == 0)
			node->value = ft_itoa(atoi(arr[1]) + 1);
		else
			node->value = ft_strdup(arr[1]);
		ft_free_env(arr);
		list_for_env(&env, node);
	}
	return (env);
}
