#include "../includes/minishell.h"

t_env	*ft_cd(t_env *env, char *buffer)
{
	char	**arg;

	arg = ft_strsplit(buffer, ' ');
	env = cd(env, arg);
	free2d(arg);
	return (env);
}

t_env	*cd(t_env *env, char **arg)
{
	if (arraylen(arg) == 1) //cd
		env = root(env);
	else if (ft_strcmp(arg[1], "-") == 0) //cd -
		env = oldpwd(env);
	else if (ft_strcmp(arg[1], "~") == 0 || ft_strncmp(arg[1], "~/", 2) == 0) //cd ~ or cd ~/
		env = root_path(env, arg[1]);
	else if (ft_strncmp(arg[1], "..", 2) == 0)//cd ..
		env = go_back(env, arg[1]);
	else
		env = cd_and_go(env, arg[1]);
	return (env);
}

t_env	*root(t_env *env)
{
	char *home;
	int check;

	home = NULL;
	check = check_env(env, "HOME");
	if (check == 0)
		ft_putendl("Error: HOME not set");
	else
	{
		home = get_env(env, "HOME");
		change_dir(home, ": No such file or directory");
		free(home);
		move_pwd(env);
	}
	return (env);
}

t_env	*oldpwd(t_env *env)
{
	char	*oldpwd;
	int		check;
	
	check = check_env(env, "OLDPWD");
	if (check == 0)
		ft_putendl("Error: OLDPWD not set");
	else
	{
		oldpwd = get_env(env, "OLDPWD");
		change_dir(oldpwd, ": No such file or directory");
		free(oldpwd);
		move_pwd(env);
	}
	return (env);
}

t_env	*root_path(t_env *env, char *path)
{
	int		check;
	char	*second_half;
	char	*home;
	char	*full_path;

	check = check_env(env, "HOME");
	if (check == 0)
		ft_putendl("Error: HOME is not set");
	else
	{
		home = get_env(env, "HOME");
		second_half = &path[1];
		if (second_half[0] != '\0')
			full_path = ft_strjoin(home, second_half);
		else
			full_path = ft_strdup(home);
		change_dir(full_path, ": No such file or directory");
		free(full_path);
		free(home);
		move_pwd(env);
	}
	return (env);
}

t_env	*go_back(t_env *env, char *path)
{
	char	**slashes;
	char	*curr_path;
	char	**path_slashes;
	size_t	slash_len;
	char	*target;

	slashes = ft_strsplit(path, '/');
	curr_path = get_env(env,"PWD");
	path_slashes = ft_strsplit(curr_path, '/');
	slash_len = arraylen(slashes);
	if (slash_len >= arraylen(path_slashes))
		target = ft_strdup("/");
	else
	{
		target = back_steps(slash_len, path_slashes);
		change_dir(target, ": No such file or directory");
		move_pwd(env);
	}
	free(target);
	free2d(slashes);
	free(curr_path);
	free2d(path_slashes);
	return (env);
}

char	*back_steps(size_t slash_len, char **path_slashes)
{
	size_t	count;
	char	*target;
	size_t	i;
	char	*tmp;

	target = (char *)malloc(sizeof(char));
	i = 0;
	count = arraylen(path_slashes);
	count -= slash_len;
	while (i < count)
	{
		tmp = ft_strjoin(target, "/");
		free(target);
		target = ft_strjoin(tmp, path_slashes[i]);
		free(tmp);
		i++;
	}
	return (target);
}

t_env	*cd_and_go(t_env *env, char *path)
{
	char	*error;

	if (access(path, F_OK) != 0)
		error = ft_strdup(": Permission denied");
	else
		error = ft_strdup(": No such file or directory");
	if (change_dir(path, error))
		move_pwd(env);
	free(error);
	return (env);
}