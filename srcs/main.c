/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:50:02 by lebourre          #+#    #+#             */
/*   Updated: 2021/06/03 20:00:29 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_cmds(char ***cmds)
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

void	print_cmd(t_lst *lst)
{
	int i;
	int j;

	if (!lst)
		return ;
	i = -1;
	while (lst->cmds[++i])
	{
		printf("> commande avec ses args respectif:\n> %s\n>\n", lst->cmds[i]);
		/*
		j = 0;
		while (lst->cmds[++j])
			printf("> %s\n", lst->cmds[j]);
		write(2, ">\n", 2);
		*/
	}
}

t_lst	*get_cmd(char *line, t_env_lst *env)
{
	t_lst	*lst;
	int		fd;
	char	*tmp;

	lst = malloc(sizeof(t_lst));
	lst->cmds = malloc(1);
	/*
	lst = NULL;
	if (*line && line)
	{
		tmp = get_historic(1);
		if ((ft_strcmp(tmp, line)) != 0)
		{
			fd = open("./historic", O_WRONLY|O_CREAT|O_APPEND);
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			close(fd);
		}
		lst = ft_split_cmd(line, ";|", env);
		free(line);
	}
	*/
	return (lst);
}

char	*get_line(int up)
{
	char	*line;
	struct	termios term;
	char	buf;
	int		len;
	int		cur_pos;
	char	*tmp;

	tcgetattr(0, &term);
	line = ft_strdup("");
	set_term_ncan();
	len = 0;
	cur_pos = 0;
	ft_putstr_fd("Brain Diff shell > ", 1);
	line = malloc(sizeof(char));
	*line = '\0';
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
				{
					ft_putstr_fd("\b", 1);
					cur_pos--;
				}
				else if (buf == 'C' && cur_pos < len)
				{
					ft_putstr_fd("\e[1C", 1);
					cur_pos++;
				}
				else if (buf == 'A' && up < historic_size())
				{
					len = ft_strlen(line);
					free(line);
					up++;
					line = get_historic(up);
//					printf("hist = %s\tcur_pos = %d\n", line, cur_pos);
					clear_and_print(len, line, cur_pos);
					cur_pos = ft_strlen(line);
					len = cur_pos;
//`					printf("\tcur_pos = %d\n", cur_pos);
				}
				else if (buf == 'B' && up != 0)
				{
					len = ft_strlen(line);
					free(line);
					up--;
					line = get_historic(up);
					clear_and_print(len, line, cur_pos);
					cur_pos = ft_strlen(line);
					len = cur_pos;
				}
			}
		}
		else if (buf == 127)  // del
		{
			if (cur_pos > 0)
			{
				line = del_char(line, cur_pos);
				clear_and_print(len, line, cur_pos);
				write(1, " \b", 2);
				cur_pos--;
				get_to_cur_pos(ft_strlen(line), cur_pos);
				len--;
			}
			/*if (cur_pos > 0)
			{
				ft_putstr_fd("\b \b", 1);
				line = del_char(line, cur_pos);
				len--;
				cur_pos--;
			}*/
//			printf("\nline = %s\n", line);
		}
		else if (buf == 3) // ctrl + c
		{
			set_term_can(term);
			exit(0);
		}
		else
		{
			if (cur_pos == len)
			{
				write(1, &buf, 1);
				line = ft_realloc(line, len + 1);
				line[len] = buf;
				len++;
				cur_pos++;
			}
			else
			{
				tmp = insert_char(ft_substr(line, 0, cur_pos),
buf, ft_substr(line, cur_pos, ft_strlen(line) - cur_pos));
				free(line);
				line = ft_strdup(tmp);
				cur_pos = ft_strlen(line);
				clear_and_print(len, line, cur_pos);
			}
		}
//		printf("buf = %c\n", buf);
//		printf("line = %s len = %lu\n", line, ft_strlen(line));
	}
	set_term_can(term);
	printf("line = %s\n", line);
	return (line);
}

int		main(int ac, char **av, char **envp)
{
	t_env_lst *env_list;
	(void)ac;
	(void)av;
	(void)envp;
	t_lst *lst;
	lst = malloc (sizeof(t_lst) + 1);
	lst->cmds = malloc (sizeof(char) + 1);
	lst->redir = malloc (sizeof(t_redir) + 1);
	lst->separator = malloc (sizeof(t_separator) + 1);

	env_list = NULL;
	env_list = get_env(env_list, envp);
	while (1)
	{
		//print_cmd(lst);
		lst = get_cmd(get_line(0), env_list);
		lst->cmds[0] = "0";
		printf("%s\n", lst->cmds[0]);
		if (lst)
		{
			get_built_in(lst, env_list);
			free_cmds(lst);
		}
	}
	return (0);
}