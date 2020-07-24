#include "../includes/minishell.h"

t_env		*init(void)
{
	extern char **environ;
	t_env		*env;
	int i;

	i = 0;
	env = NULL;
	while (environ[i] != NULL)
	{
		env = node(environ[i], env);
		i++;
	}
	return (env);
}

int		main()
{
	t_env	*env;

	env = init();
	minishell(env);
	return (0);
}