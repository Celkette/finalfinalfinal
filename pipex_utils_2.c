#include "pipex.h"

void	pipex_error_i(char *message, int i)
{
	if (i != -1)
		ft_printf("%s at index %d\n", message, i);
	else
		ft_printf("%s\n", message);
	exit(EXIT_FAILURE);
}

void	ft_free_tab(char **tab)
{
	int	i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

int	pipex_creat_open_fd_in_one(char **argv)
{
    int fd_in;

	fd_in = open(argv[1], O_RDONLY, 0644);
fprintf(stderr, "fd_in = %d\n", fd_in);
	if (fd_in == -1)
		pipex_error_i("open fd_in failed(pipex_creat_open_fd)", -1);
    return (fd_in);
}

int	pipex_creat_open_fd_out_one(int argc, char **argv)
{
    int fd_out;

	fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		pipex_error_i("open fd_out failed(pipex_creat_open_fd)", -1);
    return (fd_out);
}
