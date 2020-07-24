#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <signal.h>
# include <stdlib.h>

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

char		*read_line(void);
void		minishell(t_env *env);
t_env		*node(char *c, t_env *head);
t_env		*new_node(const char *c);
void		add_node(const char *c, t_env *head);
char		**split(const char *array);
void		print_lst(t_env *lst);
t_env		*run_unsetenv(char *buffer, t_env *env);
void		ft_unsetenv(t_env *env, char *remove);
t_env		*run_setenv(char *buffer, t_env *env);
void		ft_setenv(t_env *head, char *add);
void		free_lst(t_env *lst);
void		ft_sys(t_env *env, char *buffer);
void		scan_path(t_env *env, char **segments);
void		scan_dir(char *pathway, char **segments, t_env *env);
void		execute(char **segment, char *cur_dir, t_env *env);
t_env		*ft_cd(t_env *env, char *buffer);
t_env		*cd(t_env *env, char **arg);
t_env		*root(t_env *env);
t_env		*oldpwd(t_env *env);
t_env		*root_path(t_env *env, char *path);
t_env		*go_back(t_env *env, char *path);
char		*back_steps(size_t slash_len, char **path_slashes);
t_env		*cd_and_go(t_env *env, char *path);
int			check_env(t_env *env, char *to_find);
char		*get_env(t_env *env, char *to_get);
int			change_dir(char *path, char *message);
void		move_pwd(t_env *env);
char		*create_env(char *key, char *value);
void        ft_echo(t_env *env, char *buffer);

#endif