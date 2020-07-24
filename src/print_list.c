#include "../includes/minishell.h"

void	print_lst(t_env *list)
{
	t_env		*lst;

	lst = list;
	while (lst != NULL)
	{
		if ((lst->key) == NULL && (lst->value) == NULL)
			continue;
		else
		{
			ft_putstr(lst->key);
			ft_putchar('=');
			ft_putendl(lst->value);
		}
		lst = lst->next;
		list = lst;
	}
}