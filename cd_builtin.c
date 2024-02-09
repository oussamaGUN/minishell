#include "main.h"

void ft_cd(mini_t *mini, char **env)
{
    char buf[100];
    printf("%s\n", getcwd(buf, 130));
}