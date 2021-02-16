/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 12:10:52 by lebourre          #+#    #+#             */
/*   Updated: 2021/02/04 14:34:36 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
/*
void	get_env(t_env_lst *env_list, char **envp)
{
	int		i;
	int		j;
	int		tmp;
	char	*name;
	char	*content;

	i = -1;
	while (envp[++i])
	{
		j = -1;
		while (envp[i][++j] != '=')
			;
		name = ft_substr(envp[i], 0, j - 1);
		tmp = j + 1;
		while (envp[i][++j])
			;
		content = ft_substr(envp[i], tmp, j);
		env_list = ft_lstnew_env(name, content);
		free(name);
		free(content);
		env_list = env_list->next;
	}
}*/
