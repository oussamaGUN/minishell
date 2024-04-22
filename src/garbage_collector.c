#include "main.h"

char	*ft_malloc(size_t	size, t_free **alloc, void *mem)
{
	t_free	*new;

	new = (t_free *)malloc(sizeof(t_free));
	if (!new)
		return (NULL);
	if (!mem)
		new->mem = malloc(size);
	else
		new->mem = mem;
	if (!(new->mem))
		return (free(new), NULL);
	add_front_mem(alloc, new);
	return (new->mem);
}

void	add_front_mem(t_free **alloc, t_free *new)
{
	new->next = *alloc;
	*alloc = new;
}
void	garbage_collector(t_free **alloc)
{
	t_free	*holder;

	holder = *alloc;
	while (holder)
	{
		// printf("addr: {%p} it's free!\n",holder->mem);
		free(holder->mem);
		holder = holder->next;
	}
	free(*alloc);
	*alloc = NULL;
}












// int main(void)
// {
// 	t_free	*memory;

// 	memory = NULL;



// 	int		*number = ft_malloc(sizeof(int), &memory);
// 	char	*name = ft_malloc(sizeof(char) * 30, &memory);
// 	double	*grade = ft_malloc(sizeof(double), &memory);



// 	*number = 12;
// 	strcpy(name, "mustapha");
// 	*grade = 18.38;

// 	printf("number\t: %d\n",*number);
// 	printf("name\t: %s\n",name);
// 	printf("grade\t: %.2lf\n",*grade);


// 	// garbage_collector(memory);
// 	return (EXIT_SUCCESS);
// }
