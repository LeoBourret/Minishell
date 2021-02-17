/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:05:17 by lebourre          #+#    #+#             */
/*   Updated: 2021/02/17 17:12:36 by lebourre         ###   ########.fr       */
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

typedef struct	s_fct_params
{
	char **av;
	t_env_lst *env_list;
}				t_fct_params;

int				get_next_line(int fd, char **line);
int				get_to_next_quote(char *s, int i);
t_env_lst		*get_env(t_env_lst *list, char **envp);
int				pass_cmd_name(char *s, int i);
char			***ft_split_cmd(char *str, char *separator);
char			**ft_split_args(char *str);
t_env_lst		*ft_lstnew_env(char *v_name, char *v_content);
int				minishell_launch(char **av, char **envp);
int				minishell_cd(t_fct_params *params);
int				minishell_echo(t_fct_params *params);
int				minishell_pwd(t_fct_params *params);

#endif
