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

int	get_fd(t_cmd_lst *lst)
{
	int fd;
	int current_out;
	int	pid = fork();

	if (lst->redir->redir == 2) // >
	{
		fd = open(lst->redir->arg, O_CREAT | O_RDWR | O_TRUNC, 0644);
		dup2(fd, 1);
		lst->redir->redir = 0;
		current_out = dup(1);
		// wpid = waitpid(pid, &status, WUNTRACED);
		// while (!WIFEXITED(status) && !WIFSIGNALED(status));
		// return (fd);
	}
	else if (lst->redir->redir == 3) // >>
		printf ("REDIRE 3 \n");
	else if (lst->redir->redir == 1) // <
		printf ("REDIRE 1 \n");
	else if (pid == -1)
		perror("fork");
	return (fd);
}

int exec_ve(t_cmd_lst *lst)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	char	**args;

	pid = fork();
	args = join_args(lst->cmd, lst->args);
	if (pid == 0)
	{
		if (execvp(lst->cmd, args) == -1)
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
	free(args);
	return 1;
}



void get_built_in(t_cmd_lst *lst, t_env_lst *envlst)
{
	int fd;
	int	i;
	int	j;
	int	builtin;
	pid_t	pid;

	if (lst->redir != 0)
		fd = get_fd(lst);
	close (fd);
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
			exec_built_in(lst, envlst, fd);
			close (fd);
		}
		else
			exec_ve(lst);
		break ;
		lst = lst->next;
	}
	if (fd != 1)
		close(fd);
}
