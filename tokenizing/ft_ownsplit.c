#include "../main.h"

int	ft_word(char *s, char c)
{
	int		i;
	int flag;
	size_t	count;

	count = 0;
	i = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		count++;
		while (s[i] != c  && s[i])
		{
			if (s[i] == '\"' || s[i] == '\'')
			{
				i++;
				while (s[i] != '\"' && s[i] != '\'' && s[i])
					i++;
			}
			i++;
		}
		while (s[i] == c && s[i])
			i++;
		if (!s[i])
			break;
		i++;
	}
	return (count);
}

int	ft_len(char const *s, char c)
{
	size_t	i;

	i = 0;

    while (s[i] && s[i] != c)
	{
		if (s[i] == '\"')
		{
			i++;
			while ((s[i] != '\"' || *s == '\'') && s[i])
				i++;        
		}
	    i++;
	}
	return (i);
}

char	**ft_trim(char const *s, char c, char **arr, size_t words_count)
{
	unsigned int	j;
	unsigned int	k;
	size_t			word_len;

	k = 0;
	while (k < words_count)
	{
		j = 0;
		while (*s == c && *s)
			s++;
		if (*s == '\0')
			break ;
		word_len = ft_len(s, c);
		arr[k] = malloc(sizeof(char) * (word_len + 1));
		if (!arr[k])
			return (NULL);
        while (*s != c && *s)
	    {
			if (*s == '\"' || *s == '\'')
			{
				s++;
				arr[k][j++] = '\"';
				while ((*s != '\"' ) && *s)
				{
					arr[k][j++] = *s;
					s++;
				}
				arr[k][j++] = '\"';
				s++;
				// if (*(s + 1))
				// {
				// 	while (*s != c && *s)
				// 	{
				// 		arr[k][j++] = *s;
				// 		s++;					
				// 	}
				// }
				// else
			}
			if (*s != c && *s)
			{
		    	arr[k][j++] = *s;
				s++;
			}
	    }
		arr[k++][j] = '\0';
	}
	return (arr);
}
int ft_count_quotes(char const *s)
{
	int count1 = 0;
	int count2 = 0;
	int i = 0;
	while (s[i])
	{
		if (s[i] == '\"')
			count1++;
		else if (s[i] == '\'')
			count2++;
		i++;
	}
	if (count1 % 2 == 1)
		return 0;
	if (count2 % 2 == 1)
		return 0;
	return 1;
}
char *if_empty(char const *s)
{
	char *res = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!res)
		return NULL;
	int i = 0;
	int j = 0;
	while (s[i])
	{
		if ((s[i] == '\"' && s[i + 1] == '\"')
			|| (s[i] == '\'' && s[i + 1] == '\''))
			i += 2;
		res[j] = s[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return res;
}
char	**ft_ownsplit(char const *s, char c)
{
	size_t			words_count;
	char			**arr;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	s = if_empty(s);
	if (!s)
		return (NULL);
	if (ft_count_quotes(s) == 0)
	{
		ft_putendl_fd("missing some quotes", 2);
		return (NULL);
	}
	words_count = ft_word((char *)s, c);
	printf("%ld\n", words_count);
	arr = (char **) malloc(sizeof(char *) * (words_count + 1));
	if (!arr)
		return (NULL);
	arr = ft_trim(s, c, arr, words_count);

	arr[words_count] = NULL;
	return (arr);
}


 

//  int main(int argc, char const *argv[])
//  {

//     char **l = ft_ownsplit(argv[1], ' ');
// 	if (!l)
// 		return 1;
//     for (int i = 0;l[i];i++)
//         printf("%s %ld\n", l[i], ft_strlen(l[i]));
//     return 0;
//  }
 