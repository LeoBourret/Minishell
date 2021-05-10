/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 12:10:52 by lebourre          #+#    #+#             */
/*   Updated: 2021/05/10 21:13:00 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		get_to_next_quote(char *s, int i)
{
	int end_quote;

	end_quote = 0;
	if (s[i] == '\'')
	{
		i++;
		while (s[i])
		{
			if (s[i] == '\'' && s[i - 1] != '\\')
				end_quote = 1;
			if (end_quote == 1 && (s[i] == ' ' || s[i] == '\0'))
				break ;
			i++;
		}
	}
	else if (s[i] == '"')
	{
		i++;
		while (s[i] && s[i] != '"')
		{
			if (s[i] == '"' && s[i - 1] != '\\')
				break ;
			i++;
		}
	}
	return (i);
}

int		pass_cmd_name(char *s, int i)
{
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == ' ')
		i++;
	while (s[i] && !((s[i] >= 9 && s[i] <= 13) || s[i] == ' '))
		i++;
	return (i);
}

t_env_lst	*get_env(t_env_lst *list, char **envp)
{
	int		i;
	int		j;
	char	*name;
	char	*content;
	t_env_lst *begin;

	j = 0;
	while (envp[0][j] != '=')
		j++;
	name = ft_substr(envp[0], 0, j);
	while (envp[0][++j])
		;
	content = ft_substr(ft_strchr(envp[0], '=') + 1, 0, j);
	list = ft_lstnew_env(name, content);
	free(name);
	free(content);
	begin = list;
	i = 0;
	while (envp[++i])
	{
		j = -1;
		while (envp[i][++j] != '=')
			;
		name = ft_substr(envp[i], 0, j);
		while (envp[i][++j])
			;
		content = ft_substr(ft_strchr(envp[i], '=') + 1, 0, j);
		list->next = ft_lstnew_env(name, content);
		free(name);
		free(content);
		list = list->next;
	}
	return (begin);
}
