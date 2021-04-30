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

int		builtin_echo(char ***cmds)
{
	int i;

	i = 0;
	if ((is_n(cmds[0][1])) == 1)
	{
		i++;
		while (cmds[0][++i])
			printf("%s ", cmds[0][i]);
		printf("\b \b");
		fflush(stdout);
	}
	else
	{
		while (cmds[0][++i])
			printf("%s ", cmds[0][i]);
		printf("\n");
	}
	return (0);
}
