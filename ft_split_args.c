/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:56:25 by lebourre          #+#    #+#             */
/*   Updated: 2021/02/18 17:23:05 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_space(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int		is_sep(char c)
{
	if (c == '|' || c == ';')
		return (1);
	return (0);
}

char	*ft_strdup_space_sep(char *str)
{
	int		i;
	int		j;
	int		lenght;
	int		quote;
	char	*copy;

	lenght = -1;
	i = 0;
	quote = 0;
	while (str[++lenght] && !is_sep(str[lenght]))
	{
		if (lenght == 0 && (str[lenght] == '\'' || str[lenght] == '"'))
		{
			quote = 1;
			j = get_to_next_quote(str, lenght);
		}
		if (quote == 0 && is_space(str[lenght]))
			break ;
		else if (quote == 1 && lenght == j && str[lenght + 1] == ' ')
			break ;
		else if (quote == 1 && lenght == j && str[lenght + 1] != ' ')
		{
			while (ft_isalnum(str[++lenght]))
				i++;
			break ;
		}
		if ((str[lenght + 1] == '\'' || str[lenght + 1] == '"')
		&& str[lenght] == '\\')
			i++;
	}
	if (!(copy = malloc(sizeof(char) * i + 1)))
		return (NULL);
	i = -1;
	j = 0;
	while (++i < lenght)
	{
		if (str[i] == '\\' && str[i - 1] != '\\')
		{
			copy[j++] = str[i++ + 1];
		}
		if (!(str[i] == '\'' || str[i] == '"'))
			copy[j++] = str[i];
	}
	copy[j] = '\0';
	return (copy);
}

int		args_counter(char *str)
{
	int i;
	int count;

	i = 0;
	count = 1;
	i = pass_cmd_name(str, i);
	while (str[i] && !is_sep(str[i + 1]))
	{
		if (str[i - 1] == ' ' && (str[i] == '\'' || str[i] == '"'))
		{
			printf("ui\n");
			i = get_to_next_quote(str, i);
			count++;
		}
		else if (!is_space(str[i])
		&& (is_space(str[i + 1]) || str[i + 1] == '\0'))
			count++;
		i++;
	}
	printf("%d\n", count);
	return (count);
}

char	**ft_split_args(char *str)
{
	char	**args;
	int		args_count;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	args_count = args_counter(str);
	if (!(args = malloc(sizeof(char *) * (args_count + 1))))
		return (NULL);
	i = -1;
	j = 0;
	while (++i < args_count)
	{
		while (is_space(str[j]) && str[j])
			j++;
		args[i] = ft_strdup_space_sep(&str[j]);
		if (str[j] == '\'' || str[j] == '"')
			j = get_to_next_quote(str, j);
		while (!is_space(str[j]) && str[j])
			j++;
	}
	args[i] = 0;
	return (args);
}
