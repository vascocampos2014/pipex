#include "../pipex.h"

static int	open_outfile(t_args args)
{
	int flags;

	flags = O_CREAT | O_WRONLY;
	if (args.here_doc)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	return (open(args.outfile, flags, 0644));
}

static void	close_if_not_std(int fd)
{
	if (fd > 2)
		close(fd);
}

void	handle_pipex(t_args args, char **envp)
{
	int		i;
	int		pipefd[2];
	int		fdin;
	pid_t	pid;

	i = 0;
	if (args.here_doc)
	{
		pipe(pipefd);
		if (fork() == 0)
			exit(here_doc(pipefd, args.limiter));
		wait(NULL);
		fdin = pipefd[0];
		close(pipefd[1]);
	}
	else
		fdin = open(args.infile, O_RDONLY);
	while (i < args.cmd_count)
	{
		if (i == args.cmd_count - 1)
			pipefd[1] = open_outfile(args);
		else if (pipe(pipefd) == -1)
			exit(1);
		pid = fork();
		if (pid == 0)
		{
			if (dup2(fdin, STDIN_FILENO) == -1)
				exit(1);
			if (dup2(pipefd[1], STDOUT_FILENO) == -1)
				exit(1);
			close_if_not_std(fdin);
			close_if_not_std(pipefd[1]);
			exec_cmd(i, args, (int[]){STDIN_FILENO, STDOUT_FILENO}, envp);
		}
		close_if_not_std(fdin);
		close_if_not_std(pipefd[1]);
		fdin = pipefd[0];
		i++;
	}
	while (wait(NULL) > 0);
}