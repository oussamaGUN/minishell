#include "main.h"


t_token	*ft_check_errors(t_token *token)
{
	if (!syntax_error(token))
	{
		ft_putendl_fd("syntax error", 2);
		exit_status = 258 << 8;
		return (NULL);
	}
	return (token);
}
