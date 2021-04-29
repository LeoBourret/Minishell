#include "../includes/minishell.h"


int builtin_exit(char ***cmds)
{
	exit(0);
	return 0;
}