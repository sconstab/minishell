#include "../includes/minishell.h"

int		check_env(t_env *env, char *find)
{
	t_env *lst;

	lst = env;
	while (lst != NULL)
	{
		if (ft_strcmp(lst->key, find) == 0)
			return (1);
		lst = lst->next;
	}
	return (0);
}

char		*get_env(t_env *env, char *get)
{
	t_env *lst;

	lst = env;
	while (lst != NULL)
	{
		if (ft_strcmp(lst->key, get) == 0)
			break;
		lst = lst->next;
	}
	return (ft_strdup(lst->value));
}

int		change_dir(char *path, char *message)
{
	int flag;
	
	flag = chdir(path);
	if (flag != 0)
	{
		ft_putstr(path);
		ft_putendl(message);
		return (0);
	}
	return (1);
}

void		move_pwd(t_env *env)
{
	char *curr;
	char *full;
	char curr_dir[1024];

	bzero(curr_dir, 1024);
	getcwd(curr_dir, 1024);
	curr = get_env(env, "PWD");
	full = create_env("OLDPWD", curr);
	ft_setenv(env, full);
	free(full);
	full = create_env("PWD", curr_dir);
	ft_setenv(env, full);
	free(curr);
	free(full);
}

char	*create_env(char *key, char *value)
{
	char *tmp;
	char *env;

	tmp = ft_strjoin(key, "=");
	env = ft_strjoin(tmp, value);
	free(tmp);
	return (env);
}