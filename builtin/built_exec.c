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

int exec_built_in (t_cmd_lst *lst, t_env_lst *envlst)
{
	if (ft_strcmp(lst->cmds[0],"echo") == 0)
		return builtin_echo(lst, envlst);
	else if (ft_strcmp(lst->cmds[0],"cd") == 0)
		return builtin_cd(lst, envlst);
	else if (ft_strcmp(lst->cmds[0],"exit") == 0)
		return builtin_exit(lst);	
	else if (ft_strcmp(lst->cmds[0],"pwd") == 0)
		return builtin_pwd(lst, envlst);
	else if (ft_strcmp(lst->cmds[0],"env") == 0)
		return builtin_env(lst, envlst);
	else if (ft_strcmp(lst->cmds[0],"unset") == 0)
		return builtin_unset(lst, envlst);
	//else if (ft_strcmp(lst->cmds[0],"export") == 0)
	//	return builtin_export(lst, envlst);
	return 0;
}

int exec_ve(char **args)
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("BDSM");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("BDSM");
	}
	else
	{
		do
		{
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return 1;
}

void get_built_in (t_cmd_lst *lst, t_env_lst *envlst)
{
	int i;
	int j;
	int builtin;

	if (!lst)
		return ;
	j = -1;
	//printf ("%s\n", lst->cmds[0]); // ok
	while (lst->cmds[++j])
	{
		builtin = 0;
		i = -1;
		while (builtin_list[++i])
			if (ft_strcmp(builtin_list[i], lst->cmds[j]) == 0)
			{
				builtin = 1;
				break ;
			}
		if (builtin == 1)
			exec_built_in(lst, envlst);
		else
			exec_ve(lst->cmds);
	}
}
