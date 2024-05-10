/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 22:53:21 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/10 11:19:20 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_clear(t_env **env)
{
	t_env	*tmp;

	garbage_collector(&((*env)->mem));
	rl_clear_history();
	if ((*env)->pwd)
		free((*env)->pwd);
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

void	ft_free_env(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	*shlvl(char *s)
{
	int	n;

	n = ft_atoi(s);
	if (n < 0)
		return (ft_strdup("0"));
	else if (n > 999)
	{
		printf("%s%d%s", "minishell: warning: shell level(",
			n, ") too high, resetting to 1\n");
		return (ft_strdup("1"));
	}
	else
		return (ft_itoa(n + 1));
}

t_env	*envir(char **envp, int i)
{
	char	**arr;
	t_env	*env;
	t_env	*node;

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
		if (ft_strcmp(node->key, "SHLVL") == 0 && arr[1])
			node->value = shlvl(arr[1]);
		else if (arr[1])
			node->value = ft_strdup(arr[1]);
		node->visible = true;
		ft_free_env(arr);
		list_for_env(&env, node);
	}
	return (env);
}
