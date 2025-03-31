#include "pipex.h"

int	check_cmd(char *cmd)
{
	if (!cmd)
		return (0);
	if (access(cmd, X_OK) == 0)
		return (1);
	else
		return (-1);
}

int	pipex_check_arg(int argc, char **argv)
{
	if (check_if_heredoc (argv[1]) == 0)
	{
		if (argc < 6)
			pipex_error_i("\033[31m Mauvais nombre d'arguments\n\e[0m", -1);
		if (argc >= 6)
			return (1);
	}
	if (check_if_heredoc (argv[1]) != 0)
	{
		if (argc < 5)
			pipex_error_i("\033[31m Mauvais nombre d'arguments\n\e[0m", -1);
		if (argc >= 5)
			return (2);
	}
	return (0);
}

int	check_if_heredoc(char *argv)
{
	int	diff;

	diff = ft_strncmp(argv, "here_doc", 8);
	return (diff);
}

void	check_file(int argc, char **argv)
{
	int	fd_in;
	int fd_out;
	if (check_if_heredoc(argv[1]) != 0)
	{
		fd_in = open(argv[1], O_RDONLY, 0777);
		if (fd_in == -1)
			pipex_error_i("\033[31m Fichier d'entrée inexistant\n\e[0m", -1);
		close(fd_in);
		fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out == -1)
			pipex_error_i("\033[31m impossible de creer ou d'ouvrir outfile\n\e[0m", -1);
		close(fd_out);
	}
	if (check_if_heredoc(argv[1]) == 0)
	{
		fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd_out == -1)
			pipex_error_i("\033[31m impossible de creer fichier de sortie\n\e[0m", -1);
		close(fd_out);
	}
}

void	check_executable(char *cmd, char **env)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(cmd, env);
	if (!cmd_path || !*cmd_path || cmd_path[0] == '\0')
		pipex_error_i("\033[31m commande inexistante ou vide\n\e[0m", -1);
	free(cmd_path);
}