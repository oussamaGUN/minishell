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
		{
			if (s[i + 1] != c)
				break;
			i++;
		}
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
		if (s[i] == '\"' || s[i] == '\'')
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
			if (*s == '\"')
			{
				if (*s == '\"')
					arr[k][j++] = '\"';				
				s++;
				while (*s != '\"' && *s)
				{
					arr[k][j++] = *s;
					s++;
				}
				if (*s == '\"')
					arr[k][j++] = '\"';
				s++;
			}
			if (*s == '\'')
			{
				if (*s == '\'')
					arr[k][j++] = '\'';					
				s++;
				while (*s != '\'' && *s)
				{
					arr[k][j++] = *s;
					s++;
				}
				if (*s == '\'')
					arr[k][j++] = '\'';	
				s++;
			}
			if (*s != c && *s && *s != '\"' && *s != '\'')
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
		{
			count1++;
			i++;
			while (s[i] != '\"' && s[i])
				i++;
			if (s[i] == '\"')
				count1++;
		}
		else if (s[i] == '\'')
		{
			count2++;
			i++;
			while (s[i] != '\'' && s[i])
				i++;
			if (s[i] == '\'')
				count2++;
		}
		i++;
	}
	if (count1 % 2 == 1)
	{
		ft_putendl_fd("missing double quotes", 2);
		return 0;
	}
	if (count2 % 2 == 1)
	{
		ft_putendl_fd("missing single quotes", 2);
		return 0;
	}
	return 1;
}
char *empty(char const *s)
{
	char *res = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!res)
		return NULL;
	int i = 0;
	int j = 0;
	int flag = 0;
	while (s[i])
	{
		if (s[i] == '\"' && s[i + 1] != '\"')
		{
			i++;
			// if (s[i + 1] != '\"' && s[i])
				res[j++] = '\"';
			while (s[i] != '\"' && s[i])
			{
				res[j++] = s[i];
				i++;
			}
			if (s[i])
				res[j++] = '\"';
			i++;
		}
		else if (s[i] == '\'' && s[i + 1] != '\'')
		{
			i++;
			res[j++] = '\'';
			while (s[i] != '\'' && s[i])
			{
				res[j++] = s[i];
				i++;
			}
			if (s[i])
				res[j++] = '\'';
			i++;
		}
		if ((s[i] == '\"' && s[i + 1] == '\"' && s[i - 1] != ' ' && s[i + 2] != ' ') 
			|| (s[i] == '\'' && s[i + 1] == '\'' && s[i - 1] != ' ' && s[i + 2] != ' '))
		{
			i += 2;
		}
		res[j++] = s[i];
		i++;
	}
	res[j] = '\0';
	return res;
}
char *minisplit(char const *s)
{
	int i = 0;
	int j = 0;
	int flag = 1;
	char *res = malloc(sizeof(char) * (ft_strlen(s) + 20));
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			flag = 0;
			while (s[i] != '\"' && s[i] != '\'' && flag && s[i])
			{
				res[j++] = s[i];
				i++;
			}
		}
		if ((s[i] == '|' || s[i] == '>' || s[i] == '<') && flag)
		{
			if ((s[i] == '>' && s[i + 1] == '>') || (s[i] == '<' && s[i + 1] == '<'))
			{
				if (s[i - 1] != ' ')
					res[j++] = ' ';
				res[j++] = s[i++];
				res[j++] = s[i];
				if (s[i + 1] != ' ')
					res[j++] = ' ';
			}
			else
			{
				if (s[i - 1] != ' ')
					res[j++] = ' ';
				res[j++] = s[i];
				if (s[i + 1] != ' ')
					res[j++] = ' ';
			}
			i++;
		}
		res[j++] = s[i];
		i++;
	}
	flag = 1;
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
	s = minisplit(s);
	s = empty(s);
	if (!s)
		return (NULL);
	if (ft_count_quotes(s) == 0)	
		return (NULL);
	words_count = ft_word((char *)s, c);
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
 