#include "../includes/minishell.h"

int builtin_unset(t_cmd_lst *lst, t_env_lst *env)
{
	int	i;

	i = 0;
	while (lst->cmds[++i])
		ft_env_remove_if(&env, lst->cmds[i], &ft_strcmp);
	return 0;
}
