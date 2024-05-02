/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 20:04:09 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/01 19:04:41 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	check_dash_n(char *s)
{
	if (!s)
		return (0);
	if (*s != '-' || *(s + 1) != 'n')
		return (0);
	s++;
	while (*s)
		if (*s++ != 'n')
			return (0);
	return (1);
}

int	echo(t_token *lst)
{
	if (!(*++(lst->arr)))
		printf("\n");
	else if (check_dash_n(*(lst->arr)++))
	{
		while (check_dash_n(*(lst->arr)))
			lst->arr++;
		while (*(lst->arr))
		{
			ft_putstr_fd(*(lst->arr)++, 1);
			if (*(lst->arr))
				ft_putchar_fd(' ', 1);
		}
	}
	else
	{
		(lst->arr)--;
		while (*(lst->arr))
		{
			ft_putstr_fd(*(lst->arr)++, STDOUT_FILENO);
			if (*(lst->arr))
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	return (0);
}

bool	check_valid_identifier(char *s)
{
	if (!ft_isalpha(*s) && *s != '_')
		return (false);
	while (*s)
	{
		if (!ft_isalnum(*s))
			return (false);
		s++;
	}
	return (true);
}

int	set(t_env	*env, char *key, char *value)
{
	t_env	*tmp;
	t_env	*new;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = value;
			return (0);
		}
		tmp = tmp->next;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return (1);
	new->key = key;
	new->value = value;
	new->next = env->next;
	env->next = new;
	return (0);
}

void	sort_env(t_env *env)
{
	char	*key;
	char	*value;
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		while (tmp)
		{
			if (ft_strcmp(env->key, tmp->key) > 0)
			{
				key = env->key;
				value = env->value;
				env->key = tmp->key;
				env->value = tmp->value;
				tmp->key = key;
				tmp->value = value;
			}
			tmp = tmp->next;
		}
		env = env->next;
	}
}
