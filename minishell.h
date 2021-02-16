/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:05:17 by lebourre          #+#    #+#             */
/*   Updated: 2021/02/04 14:12:40 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"

typedef struct	s_env_lst
{
	char	*name;
	char	*content;
	struct	s_env_lst *next;
}				t_env_lst;

int				get_next_line(int fd, char **line);
int				get_to_next_quote(char *s, int i);
void			get_env(t_env_lst *env_list, char **envp);
int				pass_cmd_name(char *s, int i);
char			***ft_split_cmd(char *str, char *separator);
char			**ft_split_args(char *str);
t_env_lst		*ft_lstnew_env(char *v_name, char *v_content);

#endif
