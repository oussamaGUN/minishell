#include "main.h"

void *ft_malloc(size_t	size, t_free **alloc)
{
	void	*mem;
	t_free	*buff;

	buff = (t_free *)malloc(sizeof(t_free));
	if (!buff)
		return (NULL);
	buff->mem = malloc(size);
	if (!(buff->mem))
		return (NULL);
	buff->next = *alloc;
	*alloc = buff;
	printf("addr: {%p} alllocated!\n",buff->mem);
	system("leaks a.out");
	return (buff->mem);
}

void	garbage_collector(t_free *alloc)
{
	while (alloc)
	{
		printf("addr: {%p} it's free!\n",alloc->mem);
		free(alloc->mem);
		alloc = alloc->next;
	}
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