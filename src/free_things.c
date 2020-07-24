#include "../includes/minishell.h"

void	free_lst(t_env *list)
{
	t_env		*head;

	head = list;
	while (head != NULL)
	{
		free(head->key);
		free(head->value);
		free(head);
		head = head->next;
	}
}