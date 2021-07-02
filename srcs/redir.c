#include "../includes/minishell.h"

void    redir_type(t_cmd_lst *lst)
{
    /*
    int fd;
    int pid = fork();
    int current_out;
    char *output = lst->redir->arg;
    
    if (lst->redir->redir == 2) 
    { //if '<' char was found in string inputted by user
        fd = open(input, O_RDONLY, 0);
        dup2(fd, STDIN_FILENO);
        in = 0;
        current_in = dup(0);  // Fix for symmetry with second paragraph
    }
    
    if (lst->redir->redir == 1) 
    { //if '>' was found in string inputted by user
        fd = creat(output, 0644);
        dup2(fd, STDOUT_FILENO);
        lst->redir->redir = 0;
        current_out = dup(1);
    }
    else 
    {*/
        printf ("NON\n");
    //}
}