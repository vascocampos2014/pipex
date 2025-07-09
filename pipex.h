#ifndef PIPEX_H
#define PIPEX_H

#include "./libft/include/libft.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

typedef struct s_args
{
    char    *infile;
    char    *outfile;
    char    **cmds;
    int     cmd_count;
    int     here_doc;
    char    *limiter;
}   t_args;

int here_doc(int *pipe, char *limiter);
void free_split(char **split);
t_args init_args(int argc, char **argv);
void check_files(char *in, char *out);
char *check_command(char *cmd);
void	handle_pipex(t_args args, char **envp);
void exec_cmd(int cmd_number, t_args args, int *pipe, char **envp);

#endif