#include "../includes/minishell.h"


int builtin_exit(t_lst *lst)
{
	exit(0);
	return 0;
}