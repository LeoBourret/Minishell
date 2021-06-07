#include "../includes/minishell.h"

int	builtin_cd(t_cmd_lst *lst, t_env_lst *envlst)
{
	int	ret;

	if (lst->cmds[1] == NULL)
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

	else if (ft_strcmp(lst->cmds[1], "~") == 0)
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
		ret = chdir(lst->cmds[1]);
	if (ret == -1)
		printf("cd: %s: No such file or directory\n", lst->cmds[1]);
	return (ret);
}
