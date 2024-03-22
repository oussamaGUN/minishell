#include "main.h"

char *ft_new(char *s, char **env)
{
	char half[1024];
	int i = 0;
	while (*s != '$')
	{
		half[i] = *s;
		i++;
		s++;
	}
	half[i] = '\0';
	char **res = ft_split(s, '$');
	i = 0;
	while (res[i])
	{
		if (getenv(res[i]))
			res[i] = getenv(res[i]);
		else
			res[i] = ft_strdup("");
		i++;
	}
	i = 0;
	char *ret = ft_strdup(half);
	while (res[i])
	{
		ret = ft_strjoin(ret, res[i]);
		i++;
	}
	return ret;
}
char **ft_split_env(char *str, char **env)
{
	char **s = ft_split(str, ' ');
	int i = 0;
	while (s[i])
	{
		if (ft_strchr(s[i], '$') && ft_strncmp(s[i], "$", ft_strlen(s[i])) == 1)
			s[i] = ft_new(s[i], env);
		i++;
	}
	
	return s;
}
