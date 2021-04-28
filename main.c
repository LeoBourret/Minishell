/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:50:02 by lebourre          #+#    #+#             */
/*   Updated: 2021/04/28 15:52:37 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void set_term_ncan(void)
{
	struct termios new;

	tcgetattr(STDIN_FILENO, &new);
	new.c_lflag &= ~(ICANON | ISIG | ECHO);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &new);
}

void set_term_can(struct termios term)
{
	tcsetattr(STDIN_FILENO, TCSADRAIN, &term);
}

char	*builtin_list[] = {
	"cd",
	"echo",
	"pwd",
	"exit",
	"export",
	"env",
	"unset"
};

int exec_built_in (char ***cmds, char **env)
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
		return builtin_env(cmds);
	else if (ft_strcmp(cmds[0][0],"unset") == 0)
		return builtin_unset(cmds);
	else if (ft_strcmp(cmds[0][0],"export") == 0)
		return builtin_export(cmds);
	return 0;
}

void get_built_in (char ***cmds, char **env)
{
	int i;

	i = -1;
	while (builtin_list[++i])
	{
		if (ft_strcmp(builtin_list[i], cmds[0][0]) == 0)
			exec_built_in(cmds, env);
		// else
		// 	exec_ve(cmds[0], cmds, **env);
	}
}

int builtin_echo(char ***cmds)
{
	int i;

	i = 0;
	while (cmds[0][++i])
		printf("%s ",cmds[0][i]);
	printf("\n");
	return 0;
}

int builtin_exit(char ***cmds)
{
	exit(0);
	return 0;
}

int builtin_cd(char ***cmds)
{
	return 0;
}

int builtin_pwd(char ***cmds)
{
	return 0;
}

int builtin_unset(char ***cmds)
{
	return 0;
}

int builtin_export(char ***cmds)
{
	return 0;
}

int builtin_env(char ***cmds)
{
	return 0;
}

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

char ***get_cmd(char *line)
{
	char ***cmds;

	cmds = ft_split_cmd(line, ";|");
	free(line);
	return (cmds);
}

char *get_line()
{
	char	*line;
	struct	termios term;
	char	buf;
	int		len;

	tcgetattr(0, &term);
	line = ft_strdup("");
	set_term_ncan();
	len = 0;
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
			}
		}
		else if (buf == 127)
		{
			if (len > 0)
				ft_putstr_fd("\b \b", 1);
			len--;
			line[len] = '\0';
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
		}
//		printf("buf = %c\n", buf);
//		printf("line = %s len = %lu\n", line, ft_strlen(line));
	}
	set_term_can(term);
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
//	env_list = get_env(env_list, envp);
	while (1)
	{
		cmds = get_cmd(get_line());
		print_cmd(cmds);			
		get_built_in(cmds, envp);
		free_cmds(cmds);
	}
	return (0);
}
