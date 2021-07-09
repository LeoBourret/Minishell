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

int exec_built_in(t_cmd_lst *lst, t_env_lst *envlst, int fd)
{
	if (ft_strcmp(lst->cmd,"echo") == 0)
		return builtin_echo(lst, envlst, fd);
	else if (ft_strcmp(lst->cmd,"cd") == 0)
		return builtin_cd(lst, envlst);
	else if (ft_strcmp(lst->cmd,"exit") == 0)
		return builtin_exit(lst);
	else if (ft_strcmp(lst->cmd,"pwd") == 0)
		return builtin_pwd(lst, envlst);
	else if (ft_strcmp(lst->cmd,"env") == 0)
		return builtin_env(lst, envlst);
	else if (ft_strcmp(lst->cmd,"unset") == 0)
		return builtin_unset(lst, envlst);
	//else if (ft_strcmp(lst->cmds[0],"export") == 0)
	//	return builtin_export(lst, envlst);
	close (fd);
	return 0;
}

char	**join_args(char *s, char **args)
{
	char	**new;
	int		len;
	int		i;

	len = 0;
	while (args[len])
		len++;
	new = malloc(sizeof(char *) * (len + 2));
	len = 0;
	i = 1;
	new[0] = s;
	while (args[len])
	{
		new[i] = args[len];
		i++;
		len++;
	}
	new[i] = NULL;
	return (new);
}

void	redir(t_cmd_lst *lst)
{
	int	pid = fork();
	int status;
	int inout = lst->redir->redir;
	char *inoutput = lst->redir->arg;

	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		if (inout == 1) // <
		{
			int fd0 = open(inoutput, O_RDONLY);
			dup2(fd0, 0);
			close(fd0);
		}
		else if (inout == 2) // >
		{
			int fd1 = open(inoutput, O_CREAT | O_RDWR | O_TRUNC, 0644);
			printf("fd = %d\n", fd1);
			dup2(fd1, 1);
			close(fd1);
		}		
		else if (inout == 3) // >>
		{
			int fd1 = open(inoutput, O_CREAT | O_RDWR | O_APPEND, 0644);
			dup2(fd1, 1);
			close(fd1);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		exit(0);
	}
}

int exec_ve(t_cmd_lst *lst, int builtin, t_env_lst *envlst)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	char	**args;
	pid = fork();
	args = join_args(lst->cmd, lst->args);
	if (pid < 0)
		perror("BDSM");
	else if (pid == 0)
	{
		if (execve(lst->cmd, args, 0) == -1) // a changer pour get l'env sous forme char**
			perror("BDSM");
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	free(args);
	return 1;
}

void get_built_in(t_cmd_lst *lst, t_env_lst *envlst)
{
	int fd = 1;
	int	i;
	int	j;
	int	builtin;
	int fd0 = dup(0);
	int fd1 = dup(1);
	pid_t	pid;
	if (lst->redir != 0)
		redir(lst);
	if (!lst)
		return ;
	j = -1;
	while (lst)
	{
		builtin = 0;
		i = -1;
		while (builtin_list[++i])
			if (ft_strcmp(builtin_list[i], lst->cmd) == 0)
			{
				builtin = 1;
				break ;
			}
		if (builtin == 1)
		{
			exec_built_in(lst, envlst, 1);

		}
		else
		{
			exec_ve(lst, builtin, envlst);
		}
		dup2(fd0, 0);
		close(fd0);
		dup2(fd1, 1);
		close(fd1);
		break ;
		lst = lst->next;
	}
	if (fd != 1)
		close(fd);
}
