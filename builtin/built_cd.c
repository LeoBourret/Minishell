#include "../includes/minishell.h"

int builtin_cd(char ***cmds, t_env_lst *envlst)
{
	while (envlst)
	{
		if (ft_strcmp(envlst->name, "PWD") == 0)
			printf("%s\n", envlst->content);
		envlst = envlst->next;
	}
	return 0;
}