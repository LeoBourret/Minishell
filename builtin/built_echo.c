#include "../includes/minishell.h"

int builtin_echo(char ***cmds)
{
	int i;

	i = 0;
	if (ft_strcmp(cmds[0][1], "-n") == 0)
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
return 0;
}