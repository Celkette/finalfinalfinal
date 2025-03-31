#include "pipex.h"

void	begin_check(int argc, char **argv, char **env)
{
	char	**tab_paths;
	int		i;

	tab_paths = get_env_tab(env);
	ft_free_tab(tab_paths);
	check_file(argc, argv);
	i = 2;
	if (pipex_check_arg(argc, argv) == 1)
		i = 3;
	while (i < argc - 1)
	{
		check_executable(argv[i], env);
		i++;
	}
	return ;
}

void	execute_cmd(char **argv, char **envp, int cmd_i)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = get_cmd_arg(argv[cmd_i]);
	cmd_path = get_cmd_path(argv[cmd_i], envp);
	if (cmd_path == NULL)
	{
		ft_free_tab(cmd_args);
		pipex_error_i("Command doesn't exist or Execute denied", -1);
	}
fprintf(stderr, "cmd_path = %s\n", cmd_path);
fprintf(stderr, "cmd_args[0] = %s\n", cmd_args[0]);
    execve(cmd_path, cmd_args, envp);
	free(cmd_path);
	ft_free_tab(cmd_args);
}