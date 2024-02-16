#include "main.h"

void ft_export(mini_t *mini, char **env)
{
    env = ft_split(mini->cmd, ' ');
    printf("%s\n", env[0]);
}