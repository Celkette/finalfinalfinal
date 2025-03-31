/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-rouz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:20:54 by cle-rouz          #+#    #+#             */
/*   Updated: 2025/03/27 14:51:37 by cle-rouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "pipex.h"
# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

int		pipex_open_file(char *file, int flag);
int		pipex_creat_here_doc(char *limiter);
int		pipex_creat_open_fd_in(char **argv);
int		pipex_creat_open_fd_out(int argc, char **argv);

#endif
