/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:23:12 by lebourre          #+#    #+#             */
/*   Updated: 2021/02/03 15:19:51 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_lst		*ft_lstnew_env(char *v_name, char *v_content)
{
	t_env_lst *new;

	if (!(new = calloc(sizeof(t_env_lst))))
		return (NULL);
	new->name = ft_strdup(v_name);
	new->content = ft_strdup(v_content);
	new->next = NULL;
	return (new);
}
