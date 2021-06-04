/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 15:40:12 by lebourre          #+#    #+#             */
/*   Updated: 2021/06/04 17:00:20 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	how_many_redir(char *s)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (s[++i] && !is_sep(s[i]))
	{
		if ((i == 0 && (s[i] == '>' || s[i] == '<'))
			|| (i > 0 && (s[i] == '>' || s[i] == '<')
			&& (s[i - 1] != '\\' || s[i - 1] != '\'' || s[i - 1] != '"')))
		{
			if ((s[i] == '>' && s[i + 1] == '>')
				|| (s[i] == '<' && s[i + 1] == '<'))
				i++;
			count++;
		}
	}
	return (count);
}

char	*redir_dup(char *s)
{
	int		i;
	int		len;
	int		space;
	char	*redir;

	i = -1;
	space = 1;
	while (s[++i] && !(is_space(s[i]) && space == 1))
	{
		if (is_space(s[i]) && space == 1)
		{
			i += skip_space(&s[i]);
			space = 0;
		}
		len++;
	}
	return (redir);
}

char	**get_redir(char *s)
{
	int		i;
	int		j;
	char	**redir;
	int		redir_count;

	i = -1;
	redir_count = how_many_redir(s);
	if (redir_count == 0)
		return (NULL);
	redir = malloc(sizeof(char *) * (redir_count + 1));
	if (redir == NULL)
		return (NULL);
	j = -1;
	while (++j < redir_count)
	{
		while (s[i] && !is_redir(s, i))
			i++;
		redir[j] = redir_dup(&s[i]);
	}
	return (redir);
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
