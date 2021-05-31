#include "../includes/minishell.h"

int	builtin_cd(char ***cmds, t_env_lst *envlst)
{
	int	ret;

	if (cmds[0][1] == NULL)
	{
		while (envlst)
		{
			if (ft_strcmp("HOME", envlst->name) == 0)
				break ;
			envlst = envlst->next;
		}
		if (envlst == NULL)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 1);
			return (1);
		}
		ret = chdir(envlst->content);
	}
	else if (ft_strcmp(cmds[0][1], "~") == 0)
	{
		while (envlst)
		{
			if (ft_strcmp("HOME", envlst->name) == 0)
				break ;
			envlst = envlst->next;
		}
		ret = chdir(envlst->content);
	}
	else
		ret = chdir(cmds[0][1]);
	if (ret == -1)
		printf("cd: %s: No such file or directory\n", cmds[0][1]);
	return (ret);
}
