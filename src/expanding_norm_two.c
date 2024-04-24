#include "main.h"

char	*expand(char *s, t_env *envp)
{
	t_env	*lst;

	lst = envp;
	while (lst)
	{
		if (ft_strncmp(lst->key, s, ft_strlen(s)) == 0)
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_exit_value(t_multx *exp_vars, t_env *env)
{
	exp_vars->i++;
	exp_vars->res = ft_malloc(0, &(env->mem), ft_strjoin(exp_vars->res,
				ft_malloc(0, &(env->mem), ft_itoa(exit_status >> 8))));
	exp_vars->k = ft_strlen(exp_vars->res);
}

void	ft_delemiter(t_multx *exp_vars, char *s, t_free **mem)
{
	exp_vars->res = ft_malloc((ft_strlen(s) + 1) * 1, mem, NULL);
	if (!exp_vars->res)
		return ;
	while (s[exp_vars->i])
	{
		if (s[exp_vars->i] != '\'' && s[exp_vars->i] != '\"')
			exp_vars->res[exp_vars->j++] = s[exp_vars->i];
		exp_vars->i++;
	}
	exp_vars->res[exp_vars->j] = '\0';
}
