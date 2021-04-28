#include "minishell.h"

int builtin_echo(char ***cmds)
{
	int i;

	i = 0;
	while (cmds[0][++i])
		printf("%s ",cmds[0][i]);
	printf("\n");
	return 0;
}