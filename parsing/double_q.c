/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_q.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 10:58:26 by oussama           #+#    #+#             */
/*   Updated: 2024/03/17 16:05:49 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char *stick(char **cmd)
{
    char *join = "";
    int i = 0;
    while (cmd[i])
    {
        join = ft_strjoin(join, cmd[i]);
        join = ft_strjoin(join, " ");
        i++;
    }
    return join;
}
char	*quotes(mini_t *mini, t_pars *pars, char **env)
{
    char *res = malloc(sizeof(char) * (ft_strlen(mini->cmd)));
    if (!res)
        return NULL;
    char *exp = malloc(sizeof(char) * (ft_strlen(mini->cmd)));
    if (!exp)
        return NULL;
    int i = 0;
    int j = 0;
    int x = 0;
    while (mini->cmd[i])
    {
        if (mini->cmd[i] == '\'')
        {
            i++;
            while (mini->cmd[i] != '\'')
            {
                res[j++] = mini->cmd[i];
                i++;
            }
            i++;
        }
        else if (mini->cmd[i] == '\"')
        {
            i++;
            while (mini->cmd[i] != '\"')
            {
                exp[x++] = mini->cmd[i];
                i++;     
            }
            exp[x] = '\0';
            pars->expand = ft_split_env(exp, env);
            char *stk = stick(pars->expand);
            res = ft_strjoin(res, stk);
            i++;
            j = ft_strlen(res) - 1;
        }
        res[j++] = mini->cmd[i];
        i++;
    }
    res[j] = '\0';
    return res;
}