#include "../includes/minishell.h"

void	ft_sys(t_env *env, char *buffer)
{
	char	**seg;
	pid_t	pid;
	char	*str1;
	char	*str2;
	char	**envp;
	t_env	*head;

	head = env;
	envp = NULL;
	seg = ft_strsplit(buffer, ' ');
	while (env != NULL)
	{
		str1 = ft_strjoin(env->key, "=");
		str2 = ft_strjoin(str1, env->value);
		free(str1);
		envp = arraypush(envp, str2);
		free(str2);
		env = env->next;
	}
	if ((pid = fork()) == 0)
	{
		if (seg[0][0] == '/')
			execve(seg[0], seg, envp);
		else
			scan_path(head, seg);
		exit(1);
	}
	else
		wait(&pid);
	free2d(envp);
	free2d(seg);
}

void	scan_path(t_env *env, char **seg)
{
	char	*path;
	t_env	*head;

	path = NULL;
	head = env;
	while (env != NULL)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
		{
			path = ft_strdup(env->value);
			break;
		}
		env = env->next;
	}
	if (path)
		scan_dir(path, seg, head);
	free(path);
}

void	scan_dir(char *path, char **seg, t_env *env)
{
	DIR				*dp;
	struct dirent	*dir;
	char			**values;
	int				i;
	int				check;

	check = 0;
	values = ft_strsplit(path, ':');
	if (!values)
		return ;
	i = 0;
	while (values[i])
	{
		if ((dp = opendir(values[i])) == NULL)
		{
			i++;
			continue;
		}
		while ((dir = readdir(dp)))
		{
			if (ft_strcmp(dir->d_name, "..") == 0 || ft_strcmp(dir->d_name, ".") == 0)
				continue;
			if (ft_strcmp(seg[0], dir->d_name) == 0)
			{
				execute(seg, values[i], env);
				check = 1;
				break;
			}
		}
		if (check == 1)
			break;
		closedir(dp);
		i++;
	}
	if (check == 0)
		ft_putendl("Error: Command not found");
	free2d(values);
}

void	execute(char **seg, char *cur_dir, t_env *env)
{
	char	*str1;
	char	*str2;
	char	**envp;

	envp = NULL;

	while (env != NULL)
	{
		str1 = ft_strjoin(env->key, "=");
		str2 = ft_strjoin(str1, env->value);
		free(str1);
		envp = arraypush(envp, str2);
		free(str2);
		env = env->next;
	}
	str1 = ft_strjoin(cur_dir, "/");
	str2 = ft_strjoin(str1, seg[0]);
	execve(str2, seg, envp);
	free(str1);
	free(str2);
	free2d(envp);
}