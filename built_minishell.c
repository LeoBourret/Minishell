/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 15:37:54 by lebourre          #+#    #+#             */
/*   Updated: 2021/04/27 14:41:28 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*builtin_str[] = {
	"cd",
	"echo",
	"ls",
	"pwd",
	"help",
	"exit"
};

int		(*builtin_func[]) (t_fct_params *) = {
	&minishell_cd,
	&minishell_echo,
	&minishell_pwd
};

int		minishell_num_builtins()
{
	return (sizeof(builtin_str) / sizeof(char *));
}

int		minishell_launch(char **av, char **envp)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	pid = fork();
	if (pid == 0) 
	{
		if (execve(av[0], av, envp) == -1)
			perror("minishell");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		perror("minishell");
	else
		while (!WIFEXITED(status) && !WIFSIGNALED(status));
			wpid = waitpid(pid, &status, WUNTRACED);
	return (1);
}

int		minishell_cd(t_fct_params *params)
{
	(void)params; // avoid warning
	return (1);
}

int		minishell_echo(t_fct_params *params)
{
	int i;

	i = -1;
	while (params->av[++i])
		ft_putstr_fd(params->av[i], 0);
	write(1, "\n", 1);
	return (1);
}

int		minishell_pwd(t_fct_params *params)
{
	while (ft_strcmp(params->av[0], ft_s_tolower(params->env_list->name)) != 0
	&& params->env_list)
		params->env_list = params->env_list->next;
	ft_putstr_fd(params->env_list->content, 0);
	return (1);
}

int minishell_execute(char **args, char **envp, t_env_lst *env_list)
{
	int i;
	t_fct_params *params;

	params = malloc(sizeof(t_fct_params));
	params->av = args;
	params->env_list = env_list;
	if (args[0] == NULL)
		return 1;
	i = -1;
	while (++i < (int)minishell_num_builtins)
		if (strcmp(args[0], builtin_str[i]) == 0)
			return (*builtin_func[i])(params);
	free(params);
	return minishell_launch(args, envp);
}
