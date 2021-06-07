#include "../includes/minishell.h"

int		is_n(char *s)
{
	int i;

	i = 0;
	if (s[i] == '-')
		i++;
	else
		return (0);
	while (s[i] == 'n')
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}

int		builtin_echo(t_cmd_lst *lst, t_env_lst *env)
{
	int	i;
	int	option;

	option = 0;
	i = 1;
	while ((is_n(lst->cmds[i])) == 1)
		i++;
	if (i > 1)
		option = 1;
	while (lst->cmds[i])
	{
		if (lst->cmds[i + 1])
			printf("%s ", lst->cmds[i]);
		else
			printf("%s", lst->cmds[i]);
		i++;
	}
	if (option == 0)
		printf("\n");
	return (0);
}
