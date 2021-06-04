/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:05:17 by lebourre          #+#    #+#             */
/*   Updated: 2021/06/04 16:27:21 by lebourre         ###   ########.fr       */
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
	struct s_env_lst *next;
}				t_env_lst;

typedef struct	s_redir
{
	int		redir;
	char	**arg;
	struct s_redir *next;
}				t_redir;

typedef struct	s_separator
{
	char	separator;
	struct s_separator *next;
}				t_separator;

typedef struct	s_cmd_lst
{
	char **cmds;
	struct s_redir *redir;
	struct s_separator *separator;
	struct s_cmd_lst *next;
}				t_cmd_lst;

typedef struct	s_fct_params
{
	char **av;
	struct s_fct_params *env_list;
}				t_fct_params;

int				get_next_line(int fd, char **line);
int				get_to_next_quote(char *s, int i);
t_env_lst		*get_env(t_env_lst *list, char **envp);
int				pass_cmd_name(char *s, int i);
t_cmd_lst		*ft_new_cmd_list(void);
t_cmd_lst		*ft_split_cmd(char *str, char *separator, t_env_lst *env);
char			**ft_split_args(char *str, t_env_lst *env);
char			*insert_char(char *start, char c, char *end);
t_env_lst		*ft_lstnew_env(char *v_name, char *v_content);
int				minishell_launch(char **av, char **envp);
int				minishell_cd(t_fct_params *params);
int				minishell_echo(t_fct_params *params);
int				minishell_pwd(t_fct_params *params);
void			set_term_ncan(void);
void			set_term_can(struct termios term);
int				builtin_echo(t_cmd_lst *lst, t_env_lst *env);
int				exec_built_in (t_cmd_lst *lst, t_env_lst *envlst);
void			get_built_in (t_cmd_lst *lst, t_env_lst *envlst);
int				builtin_exit(t_cmd_lst *lst);
int				builtin_cd(t_cmd_lst *lst, t_env_lst *envlst);
int				builtin_pwd(t_cmd_lst *lst, t_env_lst *envlst);
int				builtin_unset(t_cmd_lst *lst, t_env_lst *env);
int				builtin_export(t_cmd_lst *lst, t_env_lst *envlst);
int				builtin_env(t_cmd_lst *lst, t_env_lst *envlst);
int				exec_ve(char **args);
int				minishell_execute(char **av, char **envp, t_env_lst *lst);
int				is_space(char c);
int				is_sep(char c);
int				is_redir(char *s, int index);
char			*ft_strjoin_till_space(char const *s1, char const *s2);
int				ft_whereis_char(char *s, int c);
char			*del_char(char *src, int pos);
void			clear_and_print(int len, char *s, int pos);
char			*get_historic(int up);
int				historic_size(void);
void			get_to_cur_pos(int from, int to);
void			ft_env_remove_if(t_env_lst **begin_list, void *data_ref, int (*cmp)());

#endif
