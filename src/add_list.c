#include "../includes/minishell.h"

t_env	*new_node(const char *c)
{
	t_env		*lst;
	char		**key_val;

	key_val = split(c);
	lst = (t_env *)malloc(sizeof(t_env));
	lst->key = ft_strdup(key_val[0]);
	lst->value = ft_strdup(key_val[1]);
	lst->next = NULL;
	free2d(key_val);
	return (lst);
}

void	add_node(const char *c, t_env *head)
{
	t_env	*lst;
	char	**key_val;

	lst = head;
	key_val = split(c);
	while (lst->next != NULL)
		lst = lst->next;
	lst->next = (t_env *)malloc(sizeof(t_env));
	lst->next->key = ft_strdup(key_val[0]);
	lst->next->value = ft_strdup(key_val[1]);
	lst->next->next = NULL;
	free2d(key_val);
}

t_env	*node(char *c, t_env *head)
{
	t_env	*lst;

	lst = head;
	if (head == NULL)
	{
		head = new_node(c);
		lst = head;
	}
	else
	{
		add_node(c, lst);
		head = lst;
	}
	return (head);
}

char	**split(const char *array)
{
	char	**key_val;
	int		i;
	int		j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen(array);
	key_val = (char **)malloc(sizeof(char*) * 3);
	key_val[0] = (char *)malloc(sizeof(char) * len + 1);
	key_val[1] = (char *)malloc(sizeof(char) * len + 1);
	while (array[i] != '=')
	{
		key_val[0][i] = array[i];
		i++;
	}
	key_val[0][i] = '\0';
	i++;
	while (array[i] != '\0')
	{
		key_val[1][j] = array[i];
		i++;
		j++;
	}
	key_val[1][j] = '\0';
	key_val[2] = NULL;
	return (key_val);
}