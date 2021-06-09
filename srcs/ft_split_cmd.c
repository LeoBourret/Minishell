/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:39:11 by lebourre          #+#    #+#             */
/*   Updated: 2021/06/09 12:05:50 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_separator(char c, char *separator)
{
	int i;

	i = -1;
	while (separator[++i])
		if (separator[i] == c)
			return (1);
	return (0);
}

char	*ft_strdup_sep(char *str, char *separator)
{
	int		i;
	int		lenght;
	char	*copy;

	lenght = 0;
	while (str[lenght] && !is_separator(str[lenght], separator))
		lenght++;
	if (!(copy = malloc(sizeof(char) * lenght + 1)))
		return (NULL);
	i = -1;
	while (++i < lenght)
		copy[i] = str[i];
	copy[i] = '\0';
	return (copy);
}

int		cmd_counter(char *str, char *separator)
{
	int i;
	int count;

	i = -1;
	count = 0;
	while (str[++i])
		if (!is_separator(str[i], separator)
		&& (is_separator(str[i + 1], separator) || str[i + 1] == '\0'))
			count++;
	return (count);
}
/*
char	***ft_split_cmd2(char *str, char *separator, t_env_lst *env)
{
	char	***cmds;
	int		cmd_count;
	int		i;
	int		j;

	if (!str || !*str)
		return (NULL);
	cmd_count = cmd_counter(str, separator);
	if (!(cmds = malloc(sizeof(char **) * (cmd_count + 1))))
		return (NULL);
	cmds[cmd_count] = NULL;
	i = -1;
	j = 0;
	while (++i < cmd_count)
	{
		while (is_separator(str[j], separator) && str[j])
			j++;
		cmds[i] = ft_split_args(&str[j], env);
		while (!is_separator(str[j], separator) && str[j])
			j++;
	}
	return (cmds);
}
*/
char	*get_redir(char *s)
{
	int		i;
	char	**redir;
	int		len;

	i = -1;
	len = 0;
	while (s[++i])
	{
		if ((s[i] == '>' || s[i] == '<') && i == 0)
		{
			len++;
		}
	}
	return NULL;
}

int	which_redir(char *str)
{
	if (str[0] == '<')
		return (1);
	else if (str[0] == '>')
		if (str[1] ==  '>')
			return (3);
		else
			return (2);
	else
		return (0);
}

t_cmd_lst	*ft_split_cmd(char *str, char *separator, t_env_lst *env)
{
	t_cmd_lst	*lst;
	int			cmd_count;
	int			i;
	int			j;

	if (!str || !*str)
		return (NULL);
	cmd_count = cmd_counter(str, separator);
	lst = malloc(sizeof(t_cmd_lst) * (cmd_count + 1));
	lst->redir = malloc(sizeof(t_cmd_lst) * (cmd_count + 1));
	if (!lst)
		return (NULL);
	i = 0;
	while (is_space(str[i]))
	{
		printf("Bruh\n");
		i++;
	}
	j = -1;
	while (++j < cmd_count)
	{
		if (is_separator(str[i], "><"))
		{
			lst->redir->redir = which_redir(str);
			i++;
			lst->redir->arg = &str[i];
			//printf ("\n--------- CECI EST UN PRINTF !! ---------\n\n");
			// printf ("%s\n", lst->redir->arg);
		}
			//lst->redir->redir = get_redir(&str[i]);
		if (ft_isalpha(str[i]) == 1)
			lst->cmds = ft_split_args(str, env);
		else if (is_separator(str[i], separator))
			lst->separator->separator = str[i];
		else
			printf("error\n");
		if (j + 1 != cmd_count)
		{
			// lst->next = ft_new_cmd_list();
			// lst = lst->next;
			while (!is_separator(str[i], separator))
				i++;
			i++;
		}
	}
	return lst;
}
