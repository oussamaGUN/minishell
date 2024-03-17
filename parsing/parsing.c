/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 10:56:24 by oussama           #+#    #+#             */
/*   Updated: 2024/03/17 16:02:11 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char *parsing(mini_t *mini, t_pars *pars, char **env)
{
    pars->flag = 0;
    pars->new = quotes(mini, pars, env);
    // printf("%s\n", pars->new);
    // new = single_quotes(new);
    return pars->new;
}