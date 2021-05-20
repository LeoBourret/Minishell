/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:27:19 by lebourre          #+#    #+#             */
/*   Updated: 2021/05/20 17:59:53 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*del_char(char *src, int pos)
{
	char	*res;
	int		i;

//	printf("\nline = %s\npos = %d\n", src, pos);
	res = malloc(sizeof(char *) * ft_strlen(src));
	if (res == NULL)
		return (NULL);
	i = -1;
	while (++i < pos - 1)
		res[i] = src[i];
//	printf("cc\n");
	while (src[++i])
		res[i - 1] = src[i];
	res[i - 1] = '\0';
	free(src);
//	printf("\nres = %s\n", res);
	return (res);
}

void	clear_and_print(int len, char *s, int pos)
{
	int tmp;

	tmp = 0;
	while (tmp < len)
	{
		ft_putstr_fd("\e[1C", 1);
		tmp++;
	}
	while (tmp != 0 && --tmp >= -1)
		ft_putstr_fd("\b \b", 1);
	ft_putstr_fd(s, 1);
	tmp = len;
	while (--tmp >= pos)
	{
		ft_putstr_fd("\b", 1);
	}
}

char	*get_historic(int up)
{
	int		i;
	int		fd;
	char	**line;

	up--;
	fd = open("./historic", O_RDONLY);
	line = malloc(sizeof(char *));
	i = -1;
	while ((get_next_line(fd, &line[++i])) == 1)
		line = ft_realloc_double(line);
	while (line[i])
		i++;
	while ()
}
