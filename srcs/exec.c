#include "../pipex.h"

int here_doc(int *pipe, char *limiter)
{
    char *line;
    int done = 0;
    size_t len = ft_strlen(limiter);

    while (!done)
    {
        write(1, "heredoc> ", 9);
        line = get_next_line(0);
        if (!line)
            done = 1;
        else if (!ft_strncmp(line, limiter, len) && line[len] == '\n')
        {
            free(line);
            done = 1;
        }
        else
        {
            write(pipe[1], line, ft_strlen(line));
            free(line);
        }
    }
    close(pipe[1]);
    return (0);
}

void exec_cmd(int cmd_number, t_args args, int *pipe, char **envp)
{
    char *path_cmd;
    char **flags;

    flags = ft_split(args.cmds[cmd_number], ' ');
    if (!flags)
        exit(1);
    path_cmd = check_command(flags[0]);
    if (!path_cmd)
    {
        perror("command not found");
        free_split(flags);
        exit(1);
    }
    if (dup2(pipe[0], STDIN_FILENO) == -1)
        perror("dup2 pipe[0] failed");

    if (dup2(pipe[1], STDOUT_FILENO) == -1)
        perror("dup2 pipe[1] failed");
    execve(path_cmd, flags, envp);
    perror("execve failed");
    free_split(flags);
    free(path_cmd);
    exit(1);
}

//int main()
//{
//    int in = open("in.txt", O_RDONLY);
//    int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
//    char *buffer[256];
//    read(in,buffer,256);
//    dup2(fd, STDOUT_FILENO);
//    write(1,&buffer,5);
//}