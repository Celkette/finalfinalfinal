/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_util1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-rouz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:20:04 by cle-rouz          #+#    #+#             */
/*   Updated: 2025/03/28 08:52:51 by cle-rouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	pipex_open_file(char *file, int flag)
{
	int	fd;

	fd = open(file, flag, 0644);
	if (fd == -1)
		pipex_error_i("open here_doc_fd failed(in pipex_creat_here_doc)", -1);
	return (fd);
}

int	pipex_creat_open_fd_in(char **argv)
{
    int fd_in;

	if (check_if_heredoc(argv[1]) == 0)
	{
		fd_in = pipex_creat_here_doc(argv[2]);
		if (fd_in == -1)
			pipex_error_i("creat_here_doc failed", -1);
	}
	if (check_if_heredoc(argv[1]) != 0)
	{
		fd_in = open(argv[1], O_RDONLY, 0644);
		if (fd_in == -1)
			pipex_error_i("open fd_in failed(pipex_creat_open_fd)", -1);
	}
    return (fd_in);
}

int	pipex_creat_open_fd_out(int argc, char **argv)
{
    int fd_out;
	if (check_if_heredoc(argv[1]) == 0)
	{
		fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd_out == -1)
			pipex_error_i("open fd_out failed(pipex_creat_open_fd)", -1);
	}
	if (check_if_heredoc(argv[1]) != 0)
	{
		fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out == -1)
			pipex_error_i("open fd_out failed(pipex_creat_open_fd)", -1);
	}
    return (fd_out);
}
/*
static int	annexe(int here_doc)
{
	close(here_doc);
	return (pipex_open_file("HereD.txt", O_RDONLY));
}
*/
/*
int	pipex_creat_here_doc(char *lim)
{
	int		here_doc_fd;
	char	buffer[4096];
	ssize_t	nb_read;
	ssize_t	i;
    ssize_t next_read;

	here_doc_fd = pipex_open_file("HereD.txt", O_CREAT | O_TRUNC | O_RDWR);
	nb_read = read(STDIN_FILENO, buffer, sizeof(buffer));

	while (nb_read > 0)
	{
		i = 0;
		while (i < nb_read)
		{
			if (buffer[i] == lim[0])// && (i = 0 || buffer[i -1] == '\n'))
				if ((i + ft_strlen(lim)) <= nb_read && ft_strncmp(&buffer[i], lim, ft_strlen(lim)) == 0)// && (i + ft_strlen(lim)) == nb_read)//ft_strlen(lim) == ft_strlen(&buffer[i]))
                    if ((i + ft_strlen(lim)) == nb_read)
                    {
                        next_read = read(STDIN_FILENO, buffer, sizeof(buffer));
                        if (next_read == 0)
                        {
                            close(here_doc_fd);
                            return (annexe(here_doc_fd));
                        }
                    }
			i++;
		}
		write(here_doc_fd, buffer, nb_read);
		nb_read = read(STDIN_FILENO, buffer, sizeof(buffer));
	}
	return (pipex_open_file("HereD.txt", O_RDONLY));
}
*/

int	pipex_creat_here_doc(char *lim)
{
	int		here_doc_fd;
	char	buffer[4096];
	ssize_t	nb_read;
	//ssize_t	i;
   // ssize_t next_read;

	here_doc_fd = pipex_open_file("HereD.txt", O_CREAT | O_TRUNC | O_RDWR);
	nb_read = read(STDIN_FILENO, buffer, sizeof(buffer));
	while (1)
	{
        buffer = get_next_line(here_doc_fd);
        nb_read = ft_strlen(buffer);
        if (ft_strncmp(buffer, lim, ft_strlen(lim)) != 0)
		    write(here_doc_fd, buffer, nb_read);
     //   else
        //    break;
    }
    close(here_doc_fd);
	return (pipex_open_file("HereD.txt", O_RDONLY));
}