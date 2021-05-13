/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:50:02 by lebourre          #+#    #+#             */
/*   Updated: 2021/05/13 18:06:39 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_cmds(char ***cmds)
{
	int i;
	int j;

	if (cmds)
	{
		i = -1;
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

void print_cmd(char ***cmds)
{
	int i;
	int j;

	if (!cmds)
		return ;
	i = -1;
	while (cmds[++i])
	{
		printf("> commande avec ses args respectif:\n> %s\n>\n", cmds[i][0]);
		j = 0;
		while (cmds[i][++j])
			printf("> %s\n", cmds[i][j]);
		write(2, ">\n", 2);
	}
}

char ***get_cmd(char *line, t_env_lst *env)
{
	char ***cmds;

	cmds = ft_split_cmd(line, ";|", env);
	free(line);
	return (cmds);
}

char *get_line()
{
	char	*line;
	struct	termios term;
	char	buf;
	int		len;
	int		cur_pos;

	tcgetattr(0, &term);
	line = ft_strdup("");
	set_term_ncan();
	len = 0;
	cur_pos = 0;
	ft_putstr_fd("Brain Diff shell > ", 1);
	while (1)
	{
		read(STDIN_FILENO, &buf, 1);
		if (buf == 10) // return
		{
			write(1, "\n", 1);
			break ;
		}
		else if (buf == 27) // esc
		{
			read(STDIN_FILENO, &buf, 1);
			if (buf == '[')
			{
				read(STDIN_FILENO, &buf, 1);
				if (buf == 'D' && cur_pos > 0)
					ft_putstr_fd("\b", 1);
				cur_pos--;
			}
		}
		else if (buf == 127)  // del
		{
			if (len > 0)
				ft_putstr_fd("\b \b", 1);
			len--;
			cur_pos--;
		}
		else if (buf == 3) // ctrl + c
		{
			set_term_can(term);
			exit(0);
		}
		else
		{
			write(1, &buf, 1);
			line = ft_realloc(line, len + 1);
			line[len] = buf;
			len++;
			cur_pos++;
		}
//		printf("buf = %c\n", buf);
//		printf("line = %s len = %lu\n", line, ft_strlen(line));
	}
	set_term_can(term);
	printf("line = %s\n", line);
	return (line);
}

int main(int ac, char **av, char **envp)
{
	t_env_lst *env_list;
	(void)ac;
	(void)av;
	(void)envp;
	char ***cmds;

	env_list = NULL;
	env_list = get_env(env_list, envp);
	while (1)
	{
		cmds = get_cmd(get_line(), env_list);
//		print_cmd(cmds);
		get_built_in(cmds, env_list);
		free_cmds(cmds);
	}
	return (0);
}
