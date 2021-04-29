#include "../includes/minishell.h"

int builtin_echo(char ***cmds)
{
	int i;

	i = 0;
	while (cmds[0][++i])
		printf("%s ",cmds[0][i]);
	if (ft_strcmp(cmds[0][1], "-n") != 0)
		printf("\n");
	return 0;
}