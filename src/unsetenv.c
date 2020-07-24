#include "../includes/minishell.h"

t_env	*run_unsetenv(char *buffer, t_env *env)
{
	char	**arg;

	arg = ft_strsplit(buffer, ' ');
	if (arraylen(arg) == 2)
		ft_unsetenv(env, arg[1]);
	else
		ft_putendl("Error: What is this?");
	free2d(arg);
	return (env);
}

void	ft_unsetenv(t_env *head, char *remove)
{
	t_env	*lst;
	t_env	*prev;

	lst = head;
	if (lst != NULL && (ft_strcmp(lst->key, remove) == 0))
	{
		free(lst->key);
		free(lst->value);
		head = lst->next;
		free(lst);
		return ;
	}
	while (lst != NULL && (ft_strcmp(lst->key, remove) != 0))
	{
		prev = lst;
		lst = lst->next;
	}
	if (lst == NULL)
		return;
	prev->next = lst->next;
	free(lst->key);
	free(lst->value);
	free(lst);
}