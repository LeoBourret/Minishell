/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:05:17 by lebourre          #+#    #+#             */
/*   Updated: 2021/05/11 16:09:44 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
# include <unistd.h>
# include <termios.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct	s_env_lst
{
	char	*name;
	char	*content;
	int		len;
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
char			***ft_split_cmd(char *str, char *separator, t_env_lst *env);
char			**ft_split_args(char *str, t_env_lst *env);
t_env_lst		*ft_lstnew_env(char *v_name, char *v_content);
int				minishell_launch(char **av, char **envp);
int				minishell_cd(t_fct_params *params);
int				minishell_echo(t_fct_params *params);
int				minishell_pwd(t_fct_params *params);
void			set_term_ncan(void);
void			set_term_can(struct termios term);
int				builtin_echo(char ***cmds, t_env_lst *env);
int				exec_built_in (char ***cmds, t_env_lst *envlst);
void			get_built_in (char ***cmds, t_env_lst *envlst);
int				builtin_exit(char ***cmds);
int				builtin_cd(char ***cmds);
int				builtin_pwd(char ***cmds, t_env_lst *envlst);
int				builtin_unset(char ***cmds);
int				builtin_export(char ***cmds, t_env_lst *envlst);
int				builtin_env(char ***cmds, t_env_lst *envlst);
int				exec_ve(char **args);
int				minishell_execute(char **av, char **envp, t_env_lst *lst);
int				is_space(char c);
int				is_sep(char c);

#endif
