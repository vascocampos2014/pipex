#include "../pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_args	args;

	if (argc < 5 || (ft_strncmp(argv[1], "here_doc", 8) == 0 && argc < 6))
	{
		write(2, "Usage:\n", 7);
		write(2, "  ./pipex infile cmd1 cmd2 ... cmdn outfile\n", 44);
		write(2, "  ./pipex here_doc LIMITER cmd1 ... cmdn outfile\n", 50);
		return (1);
	}
	args = init_args(argc, argv);
	handle_pipex(args, envp);
	return (0);
}