#include "../pipex.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

t_args init_args(int argc, char **argv)
{
    t_args args;
    int here_doc_mode = 0;

    here_doc_mode = (ft_strncmp(argv[1], "here_doc", 8) == 0);
    args.here_doc = here_doc_mode;

    if (here_doc_mode)
    {
        args.limiter = argv[2];
        args.cmd_count = argc - 4;
        args.cmds = &argv[3];
        args.infile = NULL;
        args.outfile = argv[argc - 1];
    }
    else
    {
        args.limiter = NULL;
        args.cmd_count = argc - 3;
        args.cmds = &argv[2];
        args.infile = argv[1];
        args.outfile = argv[argc - 1];
    }
    return args;
}

void	check_files(char *in, char *out)
{
	int	infile;
	int	outfile;

	infile = open(in, O_RDONLY);
	if (infile < 0)
		perror(in);
	outfile = open(out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (outfile < 0)
	{
		perror(out);
		exit(EXIT_FAILURE);
	}
	if (infile >= 0)
		close(infile);
	close(outfile);
}

char	*check_command(char *cmd)
{
	char	*path_cmd;
	char	*prefix;

	prefix = "/bin/";
	path_cmd = ft_strjoin(prefix, cmd);
	if (!path_cmd)
		return (NULL);
	if (access(path_cmd, X_OK) == 0)
		return (path_cmd);
	free(path_cmd);
	write(0, "Command not found in /bin\n", 27);
	return (NULL);
}