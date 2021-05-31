#include "../includes/minishell.h"

int builtin_unset(char ***cmds, t_env_lst *env)
{
	int	i;

	i = 0;
	while (cmds[0][++i])
		ft_env_remove_if(&env, cmds[0][i], &ft_strcmp);
	return 0;
}
