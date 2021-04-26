/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:50:02 by lebourre          #+#    #+#             */
/*   Updated: 2021/04/26 17:52:28 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    set_term_ncan(void)
{
	struct termios new;
	tcgetattr(STDIN_FILENO, &new);
	new.c_lflag &= ~(ICANON | ISIG | ECHO);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &new);
}

void    set_term_can(struct termios term)
{
	tcsetattr(STDIN_FILENO, TCSADRAIN, &term);
}

void	free_cmds(char ***cmds)
{
	int		i;
	int		j;

	if (cmds)
	{
		while (cmds[++i])
		{
			j = -1;
			while (cmds[i][++j])
				free(cmds[i][j]);
			free(cmds[i]);
		}
		free(cmds);
	}
}

void	print_cmd(char ***cmds)
{
	int i;
	int j;

	i = -1;
	while (cmds[++i])
	{
		printf("> coucou je suis minishell:\n> %s\n>\n", cmds[i][0]);
		j = 0;
		while (cmds[i][++j])
			printf("> %s\n", cmds[i][j]);
		write(2, ">\n", 2);
	}
}

char	***get_cmd(char *line)
{
	char ***cmds;

	cmds = NULL;
	cmds = ft_split_cmd(line, ";|");
	return (cmds);
}

char	*get_line()
{
	char	*line;
	struct termios *term;
	char buf;
	int x;

	term = (struct termios *)malloc(sizeof(struct termios));
	tcgetattr(0, term);
	line = ft_strdup("");
	set_term_ncan();
	while (1)
	{
		x = read(STDIN_FILENO, &buf, 1);
		printf("buf[0] = %d\n", buf);
		if (buf == 10 || buf == 'o')
		{
			break ;
		}
		else if (buf == 3)
		{
			set_term_can(*term);
			exit(0);
		}
		line = ft_realloc(line, 1);
		line[ft_strlen(line)] = buf;
		buf = 0;
		// status = minishell_execute(cmds[0], envp, env_list);
		// print_cmd(cmds);
	}
	set_term_can(*term);
	return (line);
}

int		main(int ac, char **av, char **envp)
{
	t_env_lst *env_list;
	(void)ac;
	(void)av;
	char ***cmds;

//	env_list = NULL;
//	env_list = get_env(env_list, envp);
	while (1)
	{
		cmds = get_cmd(get_line());
	}
	return (0);
}
