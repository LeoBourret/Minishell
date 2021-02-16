/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:50:02 by lebourre          #+#    #+#             */
/*   Updated: 2021/02/16 16:35:33 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd(char ***cmds)
{
	int i;
	int j;

	i = -1;
	while (cmds[++i])
	{
		printf("\n> coucou je suis minishell:\n> %s\n\n", cmds[i][0]);
		j = 0;
		while (cmds[i][++j])
			printf("> %s\n", cmds[i][j]);
		write(2, "\n>\n", 3);
	}
}

void	minishell_loop(void)
{
	char	*line;
	char	***cmds;
//	int		truc;

	write(2, "> ", 2);
	while (get_next_line(0, &line))
		;
	cmds = ft_split_cmd(line, "|;");
	print_cmd(cmds);
}

int		main(int ac, char **av, char **envp)
{
//	t_env_lst *env_list;
//	t_env_lst **begin_env_list;
	(void)envp;
	(void)ac;
	(void)av;
//	begin_env_list = &env_list;
//	get_env(env_list, envp);
	minishell_loop();
	return (0);
}
