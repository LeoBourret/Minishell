/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 14:24:47 by lebourre          #+#    #+#             */
/*   Updated: 2021/05/31 17:15:38 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
t_env_lst	*env_copy(t_env_lst *src)
{
	t_env_lst *begin;

	begin =
}
*/

void	ft_env_remove_if(t_env_lst **begin_list, void *data_ref, int (*cmp)())
{
	t_env_lst	*list;
	t_env_lst	*tmp;

	list = *begin_list;
	while (list && list->next)
	{
		if ((*cmp)(list->next->name, data_ref) == 0)
		{
			tmp = list->next;
			list->next = list->next->next;
			free(tmp->name);
			free(tmp->content);
			free(tmp);
		}
		list = list->next;
	}
	list = *begin_list;
	if (list && (*cmp)(list->name, data_ref) == 0)
	{
		*begin_list = list->next;
		free(list->name);
		free(list->name);
		free(list);
	}
}
