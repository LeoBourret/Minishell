/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 13:50:56 by lebourre          #+#    #+#             */
/*   Updated: 2021/05/10 15:19:41 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		env_swap(t_env_lst **curr, t_env_lst **prev, t_env_lst **begin, int i)
{
	t_env_lst	*swap;
	t_env_lst	*tmp_next;

	swap = *curr;
	tmp_next = swap->next->next;
	*curr = (*curr)->next;
	(*curr)->next = swap;
	(*curr)->next->next = tmp_next;
	if (i == 0)
		*begin = *curr;
	else
		(*prev)->next = *curr;
	*curr = *begin;
	return (0);
}

t_env_lst        *env_sort(t_env_lst *list, int i)
{
	t_env_lst	*curr;
	t_env_lst	*begin;
	t_env_lst	*prev;

	curr = list;
	begin = list;
	prev = list;
	while (curr->next)
	{
		if ((ft_strcmp(curr->name, curr->next->name)) > 0)
			i = env_swap(&curr, &prev, &begin, i);
		else
		{
			prev = curr;
			curr = curr->next;
			i++;
		}
	}
	return (begin);
}

int		builtin_export(char ***cmds, t_env_lst *envlst)
{
	t_env_lst *export_lst;
	t_env_lst *begin;

	begin = ft_lstnew_env(envlst->name, envlst->content);
	export_lst = begin;
	envlst = envlst->next;
	while (envlst)
	{
		export_lst->next = ft_lstnew_env(envlst->name, envlst->content);
		export_lst = export_lst->next;
		envlst = envlst->next;
	}
	export_lst = env_sort(begin, 0);
	while (export_lst)
	{
		printf("%s=%s\n", export_lst->name, export_lst->content);
		export_lst = export_lst->next;
	}
	return (0);
}
