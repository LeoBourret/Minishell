#include "../includes/minishell.h"

char	*builtin_list[] = {
	"cd",
	"echo",
	"pwd",
	"exit",
	"export",
	"env",
	"unset"
};

int exec_built_in (char ***cmds, t_env_lst *envlst)
{
	if (ft_strcmp(cmds[0][0],"echo") == 0)
		return builtin_echo(cmds);
	else if (ft_strcmp(cmds[0][0],"cd") == 0)
		return builtin_cd(cmds);
	else if (ft_strcmp(cmds[0][0],"exit") == 0)
		return builtin_exit(cmds);	
	else if (ft_strcmp(cmds[0][0],"pwd") == 0)
		return builtin_pwd(cmds);
	else if (ft_strcmp(cmds[0][0],"env") == 0)
		return builtin_env(cmds, envlst);
	else if (ft_strcmp(cmds[0][0],"unset") == 0)
		return builtin_unset(cmds);
	else if (ft_strcmp(cmds[0][0],"export") == 0)
		return builtin_export(cmds);
	return 0;
}

void get_built_in (char ***cmds, t_env_lst *envlst)
{
	int i;

	if (!cmds)
		return ;
	i = -1;
	while (builtin_list[++i])
	{
		if (ft_strcmp(builtin_list[i], cmds[0][0]) == 0)
			exec_built_in(cmds, envlst);
		// else
		// 	exec_ve(cmds[0], cmds, **envlst);
	}
}
