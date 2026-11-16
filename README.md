# pipex

*Part of the 42 Lisboa common core.*

`pipex` reproduces the behaviour of a shell pipeline in C. It takes an input file, any number of commands and an output file, and wires them together with `pipe()`, `fork()`, `dup2()` and `execve()`, just as the shell would.

```sh
./pipex infile "cmd1" "cmd2" ... "cmdn" outfile
# same as:  < infile cmd1 | cmd2 | ... | cmdn > outfile
```

It also supports here-documents, appending to the output file:

```sh
./pipex here_doc LIMITER "cmd1" ... "cmdn" outfile
# same as:  cmd1 << LIMITER | ... | cmdn >> outfile
```

## Build

```sh
make        # builds ./pipex (and the bundled libft)
make clean  # removes object files
make fclean # removes object files and the binary
make re     # full rebuild
```

## Example

```sh
./pipex /etc/passwd "grep bash" "cut -d: -f1" "sort" users.txt
cat users.txt
```

## How it works

- **Command lookup**: each command is split into argv and resolved against `PATH` from `envp`. Absolute and relative paths are used as they are.
- **Process chain**: one child process per command. Each child's stdin and stdout are redirected to the previous pipe and the next pipe, and the parent closes every fd it doesn't need.
- **here_doc**: lines are read from stdin until `LIMITER` and fed into the first command through a pipe.
- **Errors**: missing files, unknown commands and failed syscalls are reported on stderr, and the parent waits for every child before it exits.

## Layout

| Path | Purpose |
| --- | --- |
| `srcs/pipex.c` | Entry point and argument checks |
| `srcs/parsing.c` | Splits commands and resolves them against `PATH` |
| `srcs/exec.c` | Forks, wires pipes and handles `here_doc` |
| `srcs/handle.c` | File opening, cleanup and error handling |
| `libft/` | My libft, with `ft_printf` and `get_next_line` |
