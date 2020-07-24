#include "../includes/minishell.h"

void        print_env_var(t_env *env, char *print)
{
	t_env	*lst;

	lst = env;
	while (lst != NULL)
	{
		if (ft_strcmp(lst->key, print) == 0)
		{
            ft_putendl(lst->value);
			break;
		}
		lst = lst->next;
	}
}

char        **get_lines(char type)
{
    char    *str;
    char    **array;

    array = NULL;
    while (42)
    {
        write(1, ">", 1);
        str = read_line();
        if (strchr(str, type))
        {
            array = arraypush(array, str);
            free(str);
            break;
        }
        array = arraypush(array, str);
        free(str);
    }
    return (array);
}

void        do_print(char *str, char *exp)
{
    int     i;

    i = 0;
    while (str[i])
    {
        if (str[i] == exp[0])
        {
            i++;
            continue ;
        }
		write(1, &str[i], 1);
        i++;
    }
}

void        print_stuff(t_env *env, char **seg)
{
    int     i;
    char    *exp;

    exp = NULL;
    i = 1;
    while (seg[i])
    {
        if (seg[i][0] == '$')
        {
            print_env_var(env, &seg[i][1]);
            i++;
            continue ;
        }
        else if (exp)
            do_print(seg[i], exp);
        ft_putstr(seg[i]);
        if (seg[i + 1] != NULL)
            ft_putstr(" "); 
        i++;
    }
    ft_putstr("\n");
}

void        ft_echo(t_env *env, char *buffer)
{
    char **args;

    args = ft_strsplit(buffer, ' ');
    print_stuff(env, args);
    free2d(args);
}
